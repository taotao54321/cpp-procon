// fold_queue {{{

template<class Monoid, class F>
class FoldQueue {
private:
    F f_;
    Monoid unity_;
    // (value, folded)
    stack<pair<Monoid,Monoid>> stk_front_{};
    stack<pair<Monoid,Monoid>> stk_back_{};

public:
    FoldQueue(F&& f, const Monoid& unity) : f_(forward<F>(f)), unity_(unity) {}

    bool empty() const { return stk_front_.empty() && stk_back_.empty(); }
    Int size() const { return stk_front_.size() + stk_back_.size(); }

    Monoid fold() const {
        if(empty())
            return unity_;
        else if(stk_front_.empty())
            return stk_back_.top().second;
        else if(stk_back_.empty())
            return stk_front_.top().second;
        else
            return f_(stk_front_.top().second, stk_back_.top().second);
    }

    void push(const Monoid& x) {
        Monoid lhs = stk_back_.empty() ? unity_ : stk_back_.top().second;
        stk_back_.emplace(x, f_(lhs,x));
    }

    template<class... Args>
    void emplace(Args&&... args) {
        push(Monoid(forward<Args>(args)...));
    }

    const Monoid& front() {
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
            Monoid x0 = POP(stk_back_).first;
            stk_front_.emplace(x0, f_(unity_,x0));
            while(!stk_back_.empty()) {
                Monoid x      = POP(stk_back_).first;
                Monoid folded = f_(stk_front_.top().second, x);
                stk_front_.emplace(x, folded);
            }
        }
    }
};

template<class Monoid, class F>
FoldQueue<Monoid,F> fold_queue_make(F&& f, const Monoid& unity) {
    return FoldQueue<Monoid,F>(forward<F>(f), unity);
}

template<class Monoid, class F>
Monoid POP(FoldQueue<Monoid,F>& que) {
    Monoid x = que.front(); que.pop();
    return x;
}

// }}}
