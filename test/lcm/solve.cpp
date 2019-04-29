#include "procon.hpp"

i64 N;
vector<i64> A;

signed main() {
    RD(N);
    A = RD_ARRAY<i64>(N);

    i64 ans = ALL(accumulate, A, 1, LCM);

    PRINTLN(ans);

    EXIT();
}
