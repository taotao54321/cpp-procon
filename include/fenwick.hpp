// fenwick {{{

template<class T>
struct Fenwick {
    Int n_;
    vector<T> data_;

    explicit Fenwick(Int n) : n_(n), data_(n_+1,T{}) {}

    void add(Int i, T val) {
        for(Int v = i+1; v <= n_; v += v&-v) {
            data_[v] += val;
        }
    }

    // [0,r) の和
    T query0(Int r) const {
        T res{};
        for(Int v = r; v >= 1; v -= v&-v) {
            res += data_[v];
        }
        return res;
    }

    // [l,r) の和
    T query(Int l, Int r) const {
        ASSERT_LOCAL(l <= r);
        return query0(r) - query0(l);
    }

    // [0,r) の和が s 以上となる最小の r
    Int lower_bound(T s) const {
        if(s <= T{}) return 0;
        Int i = 0;
        for(Int v = pow2_floor(n_); v >= 1; v /= 2) {
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
    Int h_;
    Int w_;
    vector<vector<T>> data_;

    Fenwick2(Int h, Int w) : h_(h), w_(w), data_(h_+1,vector<T>(w_+1,T{})) {}

    void add(Int y, Int x, Int val) {
        for(Int i = y+1; i <= h_; i += i&-i) {
            for(Int j = x+1; j <= w_; j += j&-j) {
                data_[i][j] += val;
            }
        }
    }

    // [(0,0),(y,x)) の和
    T query0(Int y, Int x) const {
        T res{};

        for(Int i = y; i >= 1; i -= i&-i) {
            for(Int j = x; j >= 1; j -= j&-j) {
                res += data_[i][j];
            }
        }

        return res;
    }

    // [(y1,x1),(y2,x2)) の和
    T query(Int y1, Int x1, Int y2, Int x2) const {
        ASSERT_LOCAL(y1 <= y2 && x1 <= x2);
        return query0(y2,x2) - query0(y1,x2) - query0(y2,x1) + query0(y1,x1);
    }
};

// }}}
