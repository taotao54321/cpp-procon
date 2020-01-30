#include "procon.hpp"

signed main() {
    i64 N = RD();
    auto A = RD_VEC(N);

    i64 ans = ALL(FOLD1, A, LCM);

    PRINTLN(ans);

    EXIT();
}
