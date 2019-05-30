#include "procon.hpp"

signed main() {
    i64 N = RD();
    auto A = RD_ARRAY(N);

    i64 ans = ALL(accumulate, A, 1, LCM);

    PRINTLN(ans);

    EXIT();
}
