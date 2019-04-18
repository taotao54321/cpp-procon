// fenwick {{{

template<typename T>
struct Fenwick {
    vector<T> v_;

    explicit Fenwick(i64 n) : v_(n+1, 0) {}

    void add(i64 i, T x) {
        for(++i; i < SIZE(v_); i += i&(-i)) {
            v_[i] += x;
        }
    }

    // [0,n) の和
    T sum(i64 n) const {
        T res = 0;
        for(i64 i = n; i > 0; i -= i&(-i)) {
            res += v_[i];
        }
        return res;
    }

    // [i,i+n) の和
    T range(i64 i, i64 n) const {
        return sum(n) - sum(i);
    }
};

// }}}
