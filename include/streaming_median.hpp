// streaming_median {{{

// オンラインで中央値とL1ノルム最小値を求める
template<typename T>
struct StreamingMedian {
    T med_;
    priority_queue<T,vector<T>,less<T>>    los_;
    priority_queue<T,vector<T>,greater<T>> his_;
    T sum_lo_;
    T sum_hi_;

    explicit StreamingMedian(const T& med) : med_(med), sum_lo_(), sum_hi_() {}

    Int size() const { return 1 + SIZE(los_) + SIZE(his_); }

    T med_lo() const {
        return SIZE(los_) > SIZE(his_) ? los_.top() : med_;
    }

    T med_hi() const {
        return SIZE(los_) < SIZE(his_) ? his_.top() : med_;
    }

    T norm() const {
        return sum_hi_ - sum_lo_ + (SIZE(los_)-SIZE(his_))*med_;
    }

    void push(const T& x) {
        if(x < med_) {
            los_.emplace(x);
            sum_lo_ += x;
        }
        else {
            his_.emplace(x);
            sum_hi_ += x;
        }

        if(SIZE(los_) == SIZE(his_)+2) {
            T med_new = los_.top(); los_.pop();
            sum_lo_ -= med_new;
            his_.emplace(med_);
            sum_hi_ += med_;
            med_ = med_new;
        }
        else if(SIZE(los_)+2 == SIZE(his_)) {
            T med_new = his_.top(); his_.pop();
            sum_hi_ -= med_new;
            los_.emplace(med_);
            sum_lo_ += med_;
            med_ = med_new;
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
        out << "  sum_lo_: "; WRITE_REPR(out, sm.sum_lo_) << "\n";
        out << "  sum_hi_: "; WRITE_REPR(out, sm.sum_hi_) << "\n";
        out << "}";
        return out;
    }
};

// }}}
