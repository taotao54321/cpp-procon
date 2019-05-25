// streaming_median {{{

// オンラインで中央値とL1ノルム最小値を求める
template<typename T>
struct StreamingMedian {
    T med_;
    priority_queue<T,vector<T>,less<T>>    los_;
    priority_queue<T,vector<T>,greater<T>> his_;
    T norm_lo_;
    T norm_hi_;

    explicit StreamingMedian(const T& med) : med_(med), norm_lo_(), norm_hi_() {}

    i64 size() const { return 1 + SIZE(los_) + SIZE(his_); }

    T med_lo() const {
        return SIZE(los_) > SIZE(his_) ? los_.top() : med_;
    }

    T med_hi() const {
        return SIZE(los_) < SIZE(his_) ? his_.top() : med_;
    }

    T norm() const {
        return norm_lo_ + norm_hi_;
    }

    void push(const T& x) {
        if(x == med_) {
            if(SIZE(los_) <= SIZE(his_))
                los_.emplace(x);
            else
                his_.emplace(x);
        }
        else if(x < med_) {
            los_.emplace(x);
            norm_lo_ += med_ - x;
            if(SIZE(los_) == SIZE(his_)+2) {
                T med_new = los_.top(); los_.pop();
                T d = med_ - med_new;
                norm_lo_ -= (SIZE(los_)+1) * d;
                norm_hi_ += (SIZE(his_)+1) * d;
                his_.emplace(med_);
                med_ = med_new;
            }
        }
        else {  // x > med_
            his_.emplace(x);
            norm_hi_ += x - med_;
            if(SIZE(los_)+2 == SIZE(his_)) {
                T med_new = his_.top(); his_.pop();
                T d = med_new - med_;
                norm_hi_ -= (SIZE(his_)+1) * d;
                norm_lo_ += (SIZE(los_)+1) * d;
                los_.emplace(med_);
                med_ = med_new;
            }
        }
    }
};

template<typename T>
struct Formatter<StreamingMedian<T>> {
    static ostream& write_str(ostream& out, const StreamingMedian<T>& sm) {
        return write_repr(out, sm);
    }
    static ostream& write_repr(ostream& out, const StreamingMedian<T>& sm) {
        out << "StreamingMedian {\n";
        out << "  med_: "; WRITE_REPR(out, sm.med_) << "\n";
        out << "  los_: "; WRITE_REPR(out, sm.los_) << "\n";
        out << "  his_: "; WRITE_REPR(out, sm.his_) << "\n";
        out << "  norm_lo_: "; WRITE_REPR(out, sm.norm_lo_) << "\n";
        out << "  norm_hi_: "; WRITE_REPR(out, sm.norm_hi_) << "\n";
        out << "}";
        return out;
    }
};

// }}}
