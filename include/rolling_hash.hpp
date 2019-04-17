// rolling_hash {{{

struct RollingHash {
    static constexpr pair<i64,i64> BMS_DEF[] {
        {  9973,   999'999'937 },
        { 10007, 1'000'000'007 },
    };

    vector<pair<i64,i64>> bms_;
    vector<vector<i64>> hs_;
    vector<vector<i64>> bpows_;

    template<typename ForwardIt>
    RollingHash(ForwardIt first, ForwardIt last) : RollingHash(first,last,{begin(BMS_DEF),end(BMS_DEF)}) {}

    template<typename ForwardIt>
    RollingHash(ForwardIt first, ForwardIt last, const vector<pair<i64,i64>>& bms)
        : bms_(bms),
          hs_(SIZE(bms),vector<i64>(distance(first,last)+1,0)),
          bpows_(SIZE(bms),vector<i64>(distance(first,last)+1,1))
    {
        REP(i, SIZE(bms_)) {
            i64 b,m; tie(b,m) = bms_[i];
            auto& h    = hs_[i];
            auto& bpow = bpows_[i];
            auto it = first;
            REP(j, distance(first,last)) {
                auto e = *it++;
                h[j+1]    = modulo(e + h[j]*b, m);
                bpow[j+1] = modulo(bpow[j]*b, m);
            }
        }
    }

    vector<i64> get(i64 j, i64 n) const {
        vector<i64> res(SIZE(bms_));
        REP(i, SIZE(bms_)) {
            i64 m; tie(ignore,m) = bms_[i];
            const auto& h    = hs_[i];
            const auto& bpow = bpows_[i];
            res[i] = modulo(h[j+n] - h[j]*bpow[n], m);
        }
        return res;
    }
};
constexpr pair<i64,i64> RollingHash::BMS_DEF[];

template<typename ForwardIt>
RollingHash make_rolling_hash(ForwardIt first, ForwardIt last) {
    return RollingHash(first, last);
}

// }}}
