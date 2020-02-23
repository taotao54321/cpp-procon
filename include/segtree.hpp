// segtree {{{

// SegTreeRQ {{{
template<class Monoid, class Action, class FuncMonoid, class FuncAction>
struct SegTreeRQ {
    FuncMonoid fm_;
    FuncAction fa_;
    Monoid unity_monoid_;
    Int n_;
    vector<Monoid> data_;

    SegTreeRQ(FuncMonoid&& fm, FuncAction&& fa, const Monoid& unity_monoid, Int n) :
        fm_(forward<FuncMonoid>(fm)), fa_(forward<FuncAction>(fa)), unity_monoid_(unity_monoid),
        n_(n==0?0:pow2_ceil(n)), data_(2*n_,unity_monoid_)
    {
        init_merge();
    }

    SegTreeRQ(FuncMonoid&& fm, FuncAction&& fa, const Monoid& unity_monoid, Int n, const Monoid& x) :
        fm_(forward<FuncMonoid>(fm)), fa_(forward<FuncAction>(fa)), unity_monoid_(unity_monoid),
        n_(n==0?0:pow2_ceil(n)), data_(2*n_,unity_monoid_)
    {
        fill_n(begin(data_)+n_, n, x);
        init_merge();
    }

    template<class ForwardIt>
    SegTreeRQ(FuncMonoid&& fm, FuncAction&& fa, const Monoid& unity_monoid, ForwardIt first, ForwardIt last) :
        fm_(forward<FuncMonoid>(fm)), fa_(forward<FuncAction>(fa)), unity_monoid_(unity_monoid),
        n_(first==last?0:pow2_ceil(distance(first,last))), data_(2*n_,unity_monoid_)
    {
        copy(first, last, begin(data_)+n_);
        init_merge();
    }

    void act(Int i, const Action& a) {
        Int v = i + n_;
        data_[v] = fa_(data_[v], a);
        while(v > 1) {
            v /= 2;
            data_[v] = fm_(data_[2*v], data_[2*v+1]);
        }
    }

    Monoid query(Int l, Int r) const {
        ASSERT_LOCAL(l <= r);
        return query_impl(l, r, 1, 0, n_);
    }

private:
    void init_merge() {
        for(Int v = n_-1; v >= 1; --v)
            data_[v] = fm_(data_[2*v], data_[2*v+1]);
    }

    Monoid query_impl(Int lq, Int rq, Int v, Int l, Int r) const {
        if(rq <= l || r <= lq) return unity_monoid_;

        if(lq <= l && r <= rq) return data_[v];

        Int mid = (l+r) / 2;
        Monoid ml = query_impl(lq, rq, 2*v,   l, mid);
        Monoid mr = query_impl(lq, rq, 2*v+1, mid, r);
        return fm_(ml, mr);
    }
};

template<class Monoid, class Action, class FuncMonoid, class FuncAction, class T>
auto segtree_rq_make(FuncMonoid&& fm, FuncAction&& fa, const T& unity_monoid, Int n) {
    return SegTreeRQ<Monoid,Action,FuncMonoid,FuncAction>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), unity_monoid, n
    );
}

template<class Monoid, class Action, class FuncMonoid, class FuncAction, class T1, class T2>
auto segtree_rq_make(FuncMonoid&& fm, FuncAction&& fa, const T1& unity_monoid, Int n, const T2& x) {
    return SegTreeRQ<Monoid,Action,FuncMonoid,FuncAction>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), unity_monoid, n, x
    );
}

template<class Monoid, class Action, class FuncMonoid, class FuncAction, class T, class ForwardIt>
auto segtree_rq_range(FuncMonoid&& fm, FuncAction&& fa, const T& unity_monoid, ForwardIt first, ForwardIt last) {
    return SegTreeRQ<Monoid,Action,FuncMonoid,FuncAction>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), unity_monoid, first, last
    );
}
// }}}

// SegTreeRU {{{
template<class T, class Action, class FuncAction, class FuncLazy>
struct SegTreeRU {
    FuncAction fa_;
    FuncLazy fl_;
    Action unity_action_;
    Int n_;
    vector<T> data_;
    vector<Action> lazy_;

    SegTreeRU(FuncAction&& fa, FuncLazy&& fl, const Action& unity_action, Int n) :
        fa_(forward<FuncAction>(fa)), fl_(forward<FuncLazy>(fl)), unity_action_(unity_action),
        n_(n==0?0:pow2_ceil(n)), data_(n_,T{}), lazy_(2*n_,unity_action_)
    {}

    SegTreeRU(FuncAction&& fa, FuncLazy&& fl, const Action& unity_action, Int n, const T& x) :
        fa_(forward<FuncAction>(fa)), fl_(forward<FuncLazy>(fl)), unity_action_(unity_action),
        n_(n==0?0:pow2_ceil(n)), data_(n_,T{}), lazy_(2*n_,unity_action_)
    {
        fill_n(begin(data_), n, x);
    }

    template<class ForwardIt>
    SegTreeRU(FuncAction&& fa, FuncLazy&& fl, const Action& unity_action, ForwardIt first, ForwardIt last) :
        fa_(forward<FuncAction>(fa)), fl_(forward<FuncLazy>(fl)), unity_action_(unity_action),
        n_(first==last?0:pow2_ceil(distance(first,last))), data_(n_,T{}), lazy_(2*n_,unity_action_)
    {
        copy(first, last, begin(data_));
    }

    void act(Int l, Int r, const Action& a) {
        ASSERT_LOCAL(l <= r);
        if(l == r) return;
        act_impl(l, r, a, 1, 0, n_);
    }

    T query(Int i) {
        return query_impl(i, 1, 0, n_);
    }

private:
    void eval(Int v) {
        if(lazy_[v] == unity_action_) return;

        if(v >= n_) {  // leaf
            data_[v-n_] = fa_(data_[v-n_], lazy_[v]);
        }
        else {
            lazy_[2*v]   = fl_(lazy_[2*v],   lazy_[v]);
            lazy_[2*v+1] = fl_(lazy_[2*v+1], lazy_[v]);
        }
        lazy_[v] = unity_action_;
    }

    void act_impl(Int la, Int ra, Int a, Int v, Int l, Int r) {
        if(ra <= l || r <= la) return;

        if(la <= l && r <= ra) {
            lazy_[v] = fl_(lazy_[v], a);
            return;
        }

        eval(v);

        Int mid = (l+r) / 2;
        act_impl(la, ra, a, 2*v,   l, mid);
        act_impl(la, ra, a, 2*v+1, mid, r);
    }

    T query_impl(Int qi, Int v, Int l, Int r) {
        ASSERT_LOCAL(l <= qi && qi < r);

        eval(v);

        if(v >= n_) return data_[v-n_];  // leaf

        Int mid = (l+r) / 2;
        if(qi < mid)
            return query_impl(qi, 2*v, l, mid);
        else
            return query_impl(qi, 2*v+1, mid, r);
    }
};

template<class T, class Action, class FuncAction, class FuncLazy, class U>
auto segtree_ru_make(FuncAction&& fa, FuncLazy&& fl, const U& unity_action, Int n) {
    return SegTreeRU<T,Action,FuncAction,FuncLazy>(
        forward<FuncAction>(fa), forward<FuncLazy>(fl), unity_action, n
    );
}

template<class T, class Action, class FuncAction, class FuncLazy, class U1, class U2>
auto segtree_ru_make(FuncAction&& fa, FuncLazy&& fl, const U1& unity_action, Int n, const U2& x) {
    return SegTreeRU<T,Action,FuncAction,FuncLazy>(
        forward<FuncAction>(fa), forward<FuncLazy>(fl), unity_action, n, x
    );
}

template<class T, class Action, class FuncAction, class FuncLazy, class U, class ForwardIt>
auto segtree_ru_range(FuncAction&& fa, FuncLazy&& fl, const U& unity_action, ForwardIt first, ForwardIt last) {
    return SegTreeRU<T,Action,FuncAction,FuncLazy>(
        forward<FuncAction>(fa), forward<FuncLazy>(fl), unity_action, first, last
    );
}
// }}}

// SegTreeLazy {{{
template<class Monoid, class Action, class FuncMonoid, class FuncAction, class FuncLazy>
struct SegTreeLazy {
    FuncMonoid fm_;
    FuncAction fa_;
    FuncLazy fl_;
    Monoid unity_monoid_;
    Action unity_action_;
    Int n_;
    vector<Monoid> data_;
    vector<Action> lazy_;

    SegTreeLazy(FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
                const Monoid& unity_monoid, const Action& unity_action, Int n) :
        fm_(forward<FuncMonoid>(fm)), fa_(forward<FuncAction>(fa)), fl_(forward<FuncLazy>(fl)),
        unity_monoid_(unity_monoid), unity_action_(unity_action),
        n_(n==0?0:pow2_ceil(n)), data_(2*n_,unity_monoid_), lazy_(2*n_,unity_action_)
    {
        init_merge();
    }

    SegTreeLazy(FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
                const Monoid& unity_monoid, const Action& unity_action, Int n, const Monoid& x) :
        fm_(forward<FuncMonoid>(fm)), fa_(forward<FuncAction>(fa)), fl_(forward<FuncLazy>(fl)),
        unity_monoid_(unity_monoid), unity_action_(unity_action),
        n_(n==0?0:pow2_ceil(n)), data_(2*n_,unity_monoid_), lazy_(2*n_,unity_action_)
    {
        fill_n(begin(data_)+n_, n, x);
        init_merge();
    }

    template<class ForwardIt>
    SegTreeLazy(FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
                const Monoid& unity_monoid, const Action& unity_action, ForwardIt first, ForwardIt last) :
        fm_(forward<FuncMonoid>(fm)), fa_(forward<FuncAction>(fa)), fl_(forward<FuncLazy>(fl)),
        unity_monoid_(unity_monoid), unity_action_(unity_action),
        n_(first==last?0:pow2_ceil(distance(first,last))), data_(2*n_,unity_monoid_), lazy_(2*n_,unity_action_)
    {
        copy(first, last, begin(data_)+n_);
        init_merge();
    }

    void act(Int l, Int r, const Action& a) {
        ASSERT_LOCAL(l <= r);
        if(l == r) return;
        act_impl(l, r, a, 1, 0, n_);
    }

    Monoid query(Int l, Int r) {
        ASSERT_LOCAL(l <= r);
        return query_impl(l, r, 1, 0, n_);
    }

private:
    void init_merge() {
        for(Int v = n_-1; v >= 1; --v)
            data_[v] = fm_(data_[2*v], data_[2*v+1]);
    }

    void eval(Int v) {
        if(lazy_[v] == unity_action_) return;

        data_[v] = fa_(data_[v], lazy_[v]);
        if(v < n_) {  // non-leaf
            lazy_[2*v]   = fl_(lazy_[2*v],   lazy_[v]);
            lazy_[2*v+1] = fl_(lazy_[2*v+1], lazy_[v]);
        }
        lazy_[v] = unity_action_;
    }

    void act_impl(Int la, Int ra, const Action& a, Int v, Int l, Int r) {
        if(la <= l && r <= ra) {
            lazy_[v] = fl_(lazy_[v], a);
            eval(v);
            return;
        }

        eval(v);
        if(ra <= l || r <= la) return;

        Int mid = (l+r) / 2;
        act_impl(la, ra, a, 2*v,   l, mid);
        act_impl(la, ra, a, 2*v+1, mid, r);
        data_[v] = fm_(data_[2*v], data_[2*v+1]);
    }

    Monoid query_impl(Int lq, Int rq, Int v, Int l, Int r) {
        if(rq <= l || r <= lq) return unity_monoid_;

        eval(v);

        if(lq <= l && r <= rq) return data_[v];

        Int mid = (l+r) / 2;
        Monoid ml = query_impl(lq, rq, 2*v,   l, mid);
        Monoid mr = query_impl(lq, rq, 2*v+1, mid, r);
        return fm_(ml, mr);
    }
};

template<class Monoid, class Action, class FuncMonoid, class FuncAction, class FuncLazy, class T1, class T2>
auto segtree_lazy_make(FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
                       const T1& unity_monoid, const T2& unity_action, Int n)
{
    return SegTreeLazy<Monoid,Action,FuncMonoid,FuncAction,FuncLazy>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), forward<FuncLazy>(fl),
        unity_monoid, unity_action, n
    );
}

template<class Monoid, class Action, class FuncMonoid, class FuncAction, class FuncLazy, class T1, class T2, class T3>
auto segtree_lazy_make(FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
                       const T1& unity_monoid, const T2& unity_action, Int n, const T3& x)
{
    return SegTreeLazy<Monoid,Action,FuncMonoid,FuncAction,FuncLazy>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), forward<FuncLazy>(fl),
        unity_monoid, unity_action, n, x
    );
}

template<class Monoid, class Action, class FuncMonoid, class FuncAction, class FuncLazy, class T1, class T2, class ForwardIt>
auto segtree_lazy_range(FuncMonoid&& fm, FuncAction&& fa, FuncLazy&& fl,
                       const T1& unity_monoid, const T2& unity_action, ForwardIt first, ForwardIt last)
{
    return SegTreeLazy<Monoid,Action,FuncMonoid,FuncAction,FuncLazy>(
        forward<FuncMonoid>(fm), forward<FuncAction>(fa), forward<FuncLazy>(fl),
        unity_monoid, unity_action, first, last
    );
}
// }}}

// }}}
