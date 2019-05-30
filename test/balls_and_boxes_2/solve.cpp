#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N = RD();
    i64 K = RD();

    decltype(auto) fac  = factorial_table<1001>();
    decltype(auto) ifac = ifactorial_table<1001>();

    ModP ans = permutation_count_fac(K, N, fac, ifac);

    PRINTLN(ans);

    EXIT();
}
