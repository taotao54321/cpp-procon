// trisect {{{

// [lo,hi) におけるunimodalな関数 f のargmaxを返す
template<class F>
Int trisect_max_integer(Int lo, Int hi, F&& f) {
    ASSERT(lo < hi);

    while(lo+2 < hi) {
        Int x1 = lo + 1*(hi-lo)/3;
        Int x2 = lo + 2*(hi-lo)/3;
        if(f(x1) > f(x2))
            hi = x2;
        else
            lo = x1;
    }

    if(lo+1 == hi)
        return lo;
    else
        return f(lo) > f(lo+1) ? lo : lo+1;
}

template<class F>
Int trisect_min_integer(Int lo, Int hi, F&& f) {
    ASSERT(lo < hi);

    while(lo+2 < hi) {
        Int x1 = lo + 1*(hi-lo)/3;
        Int x2 = lo + 2*(hi-lo)/3;
        if(f(x1) < f(x2))
            hi = x2;
        else
            lo = x1;
    }

    if(lo+1 == hi)
        return lo;
    else
        return f(lo) < f(lo+1) ? lo : lo+1;
}

template<class F>
Real trisect_max_real(Real lo, Real hi, F&& f, Real eps=EPS) {
    ASSERT_LOCAL(!GT_EPS(lo,hi,eps));
    if(lo > hi) swap(lo, hi);

    while(!EQ_EPS(lo,hi,eps)) {
        Real x1 = lo + 1*(hi-lo)/3;
        Real x2 = lo + 2*(hi-lo)/3;
        if(f(x1) > f(x2))
            hi = x2;
        else
            lo = x1;
    }

    return (lo+hi) / 2;
}

template<class F>
Real trisect_min_real(Real lo, Real hi, F&& f, Real eps=EPS) {
    ASSERT_LOCAL(!GT_EPS(lo,hi,eps));
    if(lo > hi) swap(lo, hi);

    while(!EQ_EPS(lo,hi,eps)) {
        Real x1 = lo + 1*(hi-lo)/3;
        Real x2 = lo + 2*(hi-lo)/3;
        if(f(x1) < f(x2))
            hi = x2;
        else
            lo = x1;
    }

    return (lo+hi) / 2;
}

// }}}
