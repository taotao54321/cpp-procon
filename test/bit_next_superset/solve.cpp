#include "procon.hpp"

signed main() {
    i64 N = RD();
    i64 K = RD();

    i64 y = 0;
    REP(_, K) {
        i64 b = RD();
        y = BIT_SET(y,b);
    }

    i64 x = y;
    do {
        PRINT(x);
        PRINT(":");
        REP(i, N) {
            if(BIT_TEST(x,i)) {
                PRINT(" ");
                PRINT(i);
            }
        }
        PRINTLN();
    } while(BIT_NEXT_SUPERSET(x, N, y));

    EXIT();
}
