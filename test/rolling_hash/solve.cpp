#include "procon.hpp"
#include "rolling_hash.hpp"

signed main() {
    auto S = RD<string>();
    i64 N = SIZE(S);
    i64 M = RD();

    auto rh = ALL(make_rolling_hash, S);
    HashMap<vector<i64>,i64> cnts;
    FOR(len, 1, 11) {
        REP(i, N-len+1) {
            ++cnts[rh.get(i,len)];
        }
    }

    i64 ans = 0;
    REP(_, M) {
        auto t = RD<string>();
        auto rh2 = ALL(make_rolling_hash, t);
        ans += cnts[rh2.get(0,SIZE(t))];
    }

    PRINTLN(ans);

    EXIT();
}
