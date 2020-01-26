#include "procon.hpp"
#include "num.hpp"

signed main() {
    constexpr i64 H = 1001;
    constexpr i64 W = 1001;

    decltype(auto) fac  = factorial_table<H>();
    decltype(auto) ifac = ifactorial_table<H>();

    decltype(auto) comb   = combination_count_table<H,W>();
    auto           comb_f = combination_count_func<H,W>();

    REP(n, H) REP(r, W) {
        ModInt ans = combination_count_fac(n, r, fac, ifac);
        ASSERT(ans == comb[n][r]);
        ASSERT(ans == comb_f(n,r));
    }

    EXIT();
}
