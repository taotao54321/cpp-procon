#include "procon.hpp"
#include "cum.hpp"

void solve(i64 N) {
    Cum1<i64> cum(N);
    REP(i, N) {
        i64 a = RD();
        cum.add(i, a);
    }
    cum.build();

    i64 ans = -INF;
    FOR(i, 0, N) FOR(j, i, N) {
        i64 k = j - i + 1;
        chmax(ans, cum.query(i, k));
    }

    PRINTLN(ans);
}

signed main() {
    for(;;) {
        i64 N = RD();
        if(N == 0) break;
        solve(N);
    }

    EXIT();
}
