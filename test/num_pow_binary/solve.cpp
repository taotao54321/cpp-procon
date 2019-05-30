#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 M = RD();
    i64 N = RD();

    ModP m(M);
    ModP ans = pow_binary(m, N);

    PRINTLN(ans);

    EXIT();
}
