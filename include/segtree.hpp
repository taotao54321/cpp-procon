// segtree {{{

template<
    typename Monoid, typename Action,
    typename FuncMonoid, typename FuncAction, typename FuncLazy
>
struct SegTreeLazy {
    FuncMonoid fm_;
    FuncAction fa_;
    FuncLazy   fl_;
    Monoid unity_monoid_;
    Action unity_action_;
    i64 n_;
    vector<Monoid> data_;  // 1-based
    vector<Action> lazy_;  // 1-based

    SegTreeLazy(
        FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
        const Monoid& unity_monoid, const Action& unity_action,
        i64 n
    ) :
        fm_(forward<FuncMonoid>(fm)), fa_(forward<FuncAction>(fa)), fl_(forward<FuncLazy>(fl)),
        unity_monoid_(unity_monoid), unity_action_(unity_action),
        n_(pow2_ceil(n)), data_(2*n_,unity_monoid_), lazy_(2*n_,unity_action_)
    {
        init_merge();
    }

    SegTreeLazy(
        FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
        const Monoid& unity_monoid, const Action& unity_action,
        i64 n, const Monoid& x
    ) :
        SegTreeLazy(
            forward<FuncMonoid>(fm), forward<FuncAction>(fa), forward<FuncLazy>(fl),
            unity_monoid, unity_action,
            n
        )
    {
        SLICE(fill, data_, n_, n_+n, x);
        init_merge();
    }

    template<typename ForwardIt>
    SegTreeLazy(
        FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
        const Monoid& unity_monoid, const Action& unity_action,
        ForwardIt first, ForwardIt last
    ) :
        SegTreeLazy(
            forward<FuncMonoid>(fm), forward<FuncAction>(fa), forward<FuncLazy>(fl),
            unity_monoid, unity_action,
            distance(first,last)
        )
    {
        copy(first, last, begin(data_)+n_);
        init_merge();
    }

    void update(i64 i, i64 k, Action x) {
        update_impl(i, i+k, x, 1, 0, n_);
    }

    Monoid query(i64 i, i64 k) {
        return query_impl(i, i+k, 1, 0, n_);
    }

private:
    void init_merge() {
        for(i64 i = n_-1; i >= 1; --i)
            data_[i] = fm_(data_[node_l(i)], data_[node_r(i)]);
    }

    // [a,b): 要求区間
    // [l,r): ノード v の区間
    void update_impl(i64 a, i64 b, Action x, i64 v, i64 l, i64 r) {
        // まず現ノードを評価
        // ここで lazy_[v] が空になる
        eval(v);

        // [a,b), [l,r) が共通部分を持たなければ何もしない
        if(b <= l || r <= a) return;

        // [a,b) が [l,r) を完全に被覆するなら lazy_[v] に値を入れた後に評価
        if(a <= l && r <= b) {
            lazy_[v] = fl_(lazy_[v], x);
            eval(v);
        }
        // [a,b) が [l,r) と部分的に交わるなら子ノードを更新
        // 最後に data_[v] を更新
        else {
            i64 vl = node_l(v);
            i64 vr = node_r(v);
            update_impl(a, b, x, vl, l, (l+r)/2);
            update_impl(a, b, x, vr, (l+r)/2, r);
            data_[v] = fm_(data_[vl], data_[vr]);
        }
    }

    // [a,b): 要求区間
    // [l,r): ノード v の区間
    Monoid query_impl(i64 a, i64 b, i64 v, i64 l, i64 r) {
        // [a,b), [l,r) が共通部分を持たなければ単位元を返す
        if(b <= l || r <= a) return unity_monoid_;

        // 現ノードを評価
        eval(v);

        // [a,b) が [l,r) を完全に被覆するなら data_[v] を返す
        if(a <= l && r <= b) return data_[v];

        // [a,b) が [l,r) と部分的に交わるなら子ノードの値をマージして返す
        Monoid ml = query_impl(a, b, node_l(v), l, (l+r)/2);
        Monoid mr = query_impl(a, b, node_r(v), (l+r)/2, r);
        return fm_(ml, mr);
    }

    void eval(i64 v) {
        if(lazy_[v] == unity_action_) return;

        data_[v] = fa_(data_[v], lazy_[v]);
        if(!node_is_leaf(v)) {
            i64 vl = node_l(v);
            i64 vr = node_r(v);
            lazy_[vl] = fl_(lazy_[vl], lazy_[v]);
            lazy_[vr] = fl_(lazy_[vr], lazy_[v]);
        }

        lazy_[v] = unity_action_;
    }

    static i64 node_l(i64 v) {
        return 2*v;
    }

    static i64 node_r(i64 v) {
        return 2*v + 1;
    }

    bool node_is_leaf(i64 v) const {
        return v >= n_;
    }
};

template<
    typename Monoid, typename Action,
    typename FuncMonoid, typename FuncAction, typename FuncLazy,
    typename T1, typename T2
>
auto make_segtree_lazy(
    FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
    const T1& unity_monoid, const T2& unity_action,
    i64 n
) {
    return SegTreeLazy<Monoid,Action,FuncMonoid,FuncAction,FuncLazy>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), forward<FuncLazy>(fl),
        unity_monoid, unity_action,
        n
    );
}

template<
    typename Monoid, typename Action,
    typename FuncMonoid, typename FuncAction, typename FuncLazy,
    typename T1, typename T2, typename T3
>
auto make_segtree_lazy(
    FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
    const T1& unity_monoid, const T2& unity_action,
    i64 n,
    const T3& x
) {
    return SegTreeLazy<Monoid,Action,FuncMonoid,FuncAction,FuncLazy>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), forward<FuncLazy>(fl),
        unity_monoid, unity_action,
        n, x
    );
}

template<
    typename Monoid, typename Action,
    typename FuncMonoid, typename FuncAction, typename FuncLazy,
    typename T1, typename T2, typename ForwardIt
>
auto make_segtree_lazy_range(
    FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
    const T1& unity_monoid, const T2& unity_action,
    ForwardIt first, ForwardIt last
) {
    return SegTreeLazy<Monoid,Action,FuncMonoid,FuncAction,FuncLazy>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), forward<FuncLazy>(fl),
        unity_monoid, unity_action,
        first, last
    );
}

// }}}
