// rolling_hash {{{

struct RollingHash {
    static constexpr i64 M     = (1LL<<61)-1;
    static constexpr i64 B_DEF = 10007;

    i64 n_;
    i64 b_;
    vector<i64> bpow_;
    vector<i64> h_;

    template<typename ForwardIt>
    RollingHash(ForwardIt first, ForwardIt last) : RollingHash(first,last,B_DEF) {}

    template<typename ForwardIt>
    RollingHash(ForwardIt first, ForwardIt last, i64 b) :
        n_(distance(first,last)), b_(b), bpow_(n_+1,1), h_(n_+1,0)
    {
        auto it = first;
        REP(i, n_) {
            auto e = *it++;
            h_[i+1]    = mod(e + mul(b_,h_[i]));
            bpow_[i+1] = mod(mul(b_,bpow_[i]));
        }
    }

    i64 get(i64 i, i64 k) const {
        return mod(h_[i+k] - mul(h_[i],bpow_[k]));
    }

private:
    static i64 mul(i64 x, i64 y) {
        i64 xh = x >> 31;
        i64 xl = x & ((1LL<<31)-1);
        i64 yh = y >> 31;
        i64 yl = y & ((1LL<<31)-1);
        i64 mid  = xh*yl + xl*yh;
        i64 midh = mid >> 30;
        i64 midl = mid & ((1LL<<30)-1);
        return 2*xh*yh + xl*yl + midh + midl*(1LL<<31);
    }

    static i64 mod(i64 x) {
        i64 res = x % M;
        if(res < 0) res += M;
        return res;
    }
};

template<typename ForwardIt>
RollingHash make_rolling_hash(ForwardIt first, ForwardIt last) {
    return RollingHash(first, last);
}

template<typename ForwardIt>
RollingHash make_rolling_hash(ForwardIt first, ForwardIt last, i64 b) {
    return RollingHash(first, last, b);
}

// }}}
