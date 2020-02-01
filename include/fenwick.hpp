// fenwick {{{

template<class T>
struct Fenwick {
    i64 n_;
    vector<T> data_;

    explicit Fenwick(i64 n) : n_(n), data_(n_+1,T{}) {}

    void add(i64 i, T val) {
        for(i64 v = i+1; v <= n_; v += v&-v) {
            data_[v] += val;
        }
    }

    // [0,r) の和
    T query0(i64 r) const {
        T res{};
        for(i64 v = r; v >= 1; v -= v&-v) {
            res += data_[v];
        }
        return res;
    }

    // [l,r) の和
    T query(i64 l, i64 r) const {
        ASSERT_LOCAL(l <= r);
        return query0(r) - query0(l);
    }

    // [0,r) の和が s 以上となる最小の r
    i64 lower_bound(T s) const {
        if(s <= T{}) return 0;
        i64 i = 0;
        for(i64 v = pow2_floor(n_); v >= 1; v /= 2) {
            // 0 の要素もあるので、等号は付けない
            if(i+v <= n_ && data_[i+v] < s) {
                s -= data_[i+v];
                i += v;
            }
        }
        return i+1;
    }
};

template<class T>
struct Fenwick2 {
    i64 h_;
    i64 w_;
    vector<vector<T>> data_;

    Fenwick2(i64 h, i64 w) : h_(h), w_(w), data_(h_+1,vector<T>(w_+1,T{})) {}

    void add(i64 y, i64 x, i64 val) {
        for(i64 i = y+1; i <= h_; i += i&-i) {
            for(i64 j = x+1; j <= w_; j += j&-j) {
                data_[i][j] += val;
            }
        }
    }

    // [(0,0),(y,x)) の和
    T query0(i64 y, i64 x) const {
        T res{};

        for(i64 i = y; i >= 1; i -= i&-i) {
            for(i64 j = x; j >= 1; j -= j&-j) {
                res += data_[i][j];
            }
        }

        return res;
    }

    // [(y1,x1),(y2,x2)) の和
    T query(i64 y1, i64 x1, i64 y2, i64 x2) const {
        ASSERT_LOCAL(y1 <= y2 && x1 <= x2);
        return query0(y2,x2) - query0(y1,x2) - query0(y2,x1) + query0(y1,x1);
    }
};

// }}}
