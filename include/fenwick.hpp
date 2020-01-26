// fenwick {{{

template<class T>
struct Fenwick {
    vector<T> v_;

    explicit Fenwick(i64 n) : v_(n+1, T(0)) {}

    void add(i64 i, T x) {
        for(++i; i < SIZE(v_); i += i&(-i)) {
            v_[i] += x;
        }
    }

    T query(i64 i, i64 n) const {
        if(i == 0) return query0(i+n);
        return query0(i+n) - query0(i);
    }

private:
    // [0,n) の和
    T query0(i64 n) const {
        T res(0);
        for(i64 i = n; i > 0; i -= i&(-i)) {
            res += v_[i];
        }
        return res;
    }
};

// }}}
