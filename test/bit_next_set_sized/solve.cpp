#include "procon.hpp"

signed main() {
    i64 N; RD(N);
    i64 K; RD(K);

    i64 x = (1LL<<K)-1;
    do {
        vector<i64> ans;
        REP(i, N) {
            if(BIT_TEST(x,i))
                ans.emplace_back(i);
        }
        PRINT(x);
        PRINT(": ");
        PRINTLN(ans);
    } while(BIT_NEXT_SET_SIZED(x, N));

    EXIT();
}
