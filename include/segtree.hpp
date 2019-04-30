// segtree (monoid が必要) {{{

template<typename T, typename Op>
struct SegTree {
    using M = Monoid<T,Op>;

    i64 n_orig_;
    i64 n_;
    vector<T> v_;
    Op op_;

    explicit SegTree(i64 n) {
        init(n);
        ALL(fill, v_, M::UNITY());
    }

    SegTree(i64 n, const T& x) {
        init(n);
        i64 i = n_;
        for(; i < n_+n_orig_; ++i)
            v_[i] = x;
        for(; i < 2*n_; ++i)
            v_[i] = M::UNITY();
        for(i = n_-1; i >= 1; --i)
            v_[i] = op_(v_[2*i], v_[2*i+1]);
    }

    template<typename ForwardIt>
    SegTree(ForwardIt first, ForwardIt last) {
        init(distance(first, last));
        i64 i = n_;
        for(; first != last; ++i, ++first)
            v_[i] = *first;
        for(; i < 2*n_; ++i)
            v_[i] = M::UNITY();
        for(i = n_-1; i >= 1; --i)
            v_[i] = op_(v_[2*i], v_[2*i+1]);
    }

    void add(i64 i, i64 x) {
        update(i, v_[n_+i]+x);
    }

    void update(i64 i, i64 x) {
        i += n_;
        v_[i] = x;
        while(i > 1) {
            i /= 2;
            v_[i] = op_(v_[2*i], v_[2*i+1]);
        }
    }

    i64 query(i64 i, i64 k) const {
        assert(0 <= i && i+k <= n_orig_);
        return query_impl(i, i+k, 1, 0, n_);
    }

private:
    void init(i64 n) {
        n_orig_ = n;
        n_ = pow2_ceil(n_orig_);
        v_.resize(2*n_);
    }

    i64 query_impl(i64 a, i64 b, i64 i, i64 l, i64 r) const {
        if(r <= a || b <= l) return M::UNITY();
        if(a <= l && r <= b) return v_[i];

        i64 xl = query_impl(a, b, 2*i,   l, (l+r)/2);
        i64 xr = query_impl(a, b, 2*i+1, (l+r)/2, r);
        return op_(xl, xr);
    }
};

template<typename T, typename Op>
struct Formatter<SegTree<T,Op>> {
    static ostream& write_str(ostream& out, const SegTree<T,Op>& segtree) {
        return WRITE_RANGE_STR(out, begin(segtree.v_), end(segtree.v_));
    }
    // TODO: 桁数が多くなると崩れる
    static ostream& write_repr(ostream& out, const SegTree<T,Op>& segtree) {
        out << "SegTree {\n";
        auto it = begin(segtree.v_) + 1;
        i64 k_ini = log2_floor(segtree.n_);
        for(i64 k = k_ini; k >= 0; --k) {
            i64 m = 1LL<<(k_ini-k);
            string margin((1LL<<k)-1, ' ');
            string space((1LL<<(k+1))-1, ' ');
            out << margin;
            WRITE_JOIN_REPR(out, it, it+m, space);
            out << "\n";
            it += m;
        }
        out << "}\n";
        return out;
    }
};

// }}}
