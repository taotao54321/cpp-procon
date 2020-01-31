// serial {{{

struct Serial {
    i64 v_;
    i64 step_;

    explicit Serial(i64 start, i64 step=1) : v_(start), step_(step) {}

    i64 next() {
        i64 res = v_;
        v_ += step_;
        return res;
    }

    i64 peek() const {
        return v_;
    }
};

// }}}
