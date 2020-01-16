// fold_queue {{{

template<typename T, typename F>
class FoldQueue {
private:
    // (value, folded)
    stack<pair<T,T>> stk_front_{};
    stack<pair<T,T>> stk_back_{};
    F f_;

public:
    explicit FoldQueue(F&& f) : f_(forward<F>(f)) {}

    bool empty() const { return stk_front_.empty() && stk_back_.empty(); }
    i64 size() const { return stk_front_.size() + stk_back_.size(); }

    T fold() const {
        ASSERT(!empty());
        if(stk_front_.empty())
            return stk_back_.top().second;
        else if(stk_back_.empty())
            return stk_front_.top().second;
        else
            return f_(stk_front_.top().second, stk_back_.top().second);
    }

    void push(const T& x) {
        if(stk_back_.empty()) {
            stk_back_.emplace(x, x);
        }
        else {
            T folded = f_(stk_back_.top().second, x);
            stk_back_.emplace(x, folded);
        }
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        push(T(forward<Args>(args)...));
    }

    const T& front() {
        prepare_pop();
        return stk_front_.top().first;
    }

    void pop() {
        prepare_pop();
        stk_front_.pop();
    }

private:
    void prepare_pop() {
        ASSERT(!empty());
        if(stk_front_.empty()) {
            T x0 = POP(stk_back_).first;
            stk_front_.emplace(x0, x0);
            while(!stk_back_.empty()) {
                T x      = POP(stk_back_).first;
                T folded = f_(stk_front_.top().second, x);
                stk_front_.emplace(x, folded);
            }
        }
    }
};

template<typename T, typename F>
FoldQueue<T,F> make_fold_queue(F&& f) {
    return FoldQueue<T,F>(forward<F>(f));
}

// }}}
