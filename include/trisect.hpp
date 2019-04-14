// trisect {{{

// [lo,hi) におけるunimodalな関数 f のargmaxを返す
template<typename F>
i64 trisect_max_integer(i64 lo, i64 hi, F f) {
    assert(lo < hi);

    while(lo+2 < hi) {
        i64 x1 = lo + 1*(hi-lo)/3;
        i64 x2 = lo + 2*(hi-lo)/3;
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

template<typename F>
i64 trisect_min_integer(i64 lo, i64 hi, F f) {
    assert(lo < hi);

    while(lo+2 < hi) {
        i64 x1 = lo + 1*(hi-lo)/3;
        i64 x2 = lo + 2*(hi-lo)/3;
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

template<typename F>
f64 trisect_max_real(f64 lo, f64 hi, F f, i64 iter=100) {
    assert(lo < hi);

    REP(_, iter) {
        f64 x1 = lo + 1*(hi-lo)/3;
        f64 x2 = lo + 2*(hi-lo)/3;
        if(f(x1) > f(x2))
            hi = x2;
        else
            lo = x1;
    }

    return (lo+hi) / 2;
}

template<typename F>
f64 trisect_min_real(f64 lo, f64 hi, F f, i64 iter=100) {
    assert(lo < hi);

    REP(_, iter) {
        f64 x1 = lo + 1*(hi-lo)/3;
        f64 x2 = lo + 2*(hi-lo)/3;
        if(f(x1) < f(x2))
            hi = x2;
        else
            lo = x1;
    }

    return (lo+hi) / 2;
}

// }}}
