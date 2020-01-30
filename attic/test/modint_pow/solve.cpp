#include "procon.hpp"

signed main() {
    i64 M = RD();
    i64 N = RD();

    ModInt m(M);
    ModInt ans = m.pow(N);

    PRINTLN(ans);

    EXIT();
}
