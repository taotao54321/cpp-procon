#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N = RD();
    i64 K = RD();

    decltype(auto) fac  = factorial_table<1001>();
    decltype(auto) ifac = ifactorial_table<1001>();

    ModP ans = 0;
    FOR(i, 1, K+1) {
        ModP cur = 0;
        FOR(j, 0, i+1) {
            i64 sign = is_even(j) ? 1 : -1;
            cur += sign * combination_count_fac(i,j,fac,ifac) * pow_binary(ModP(i-j),N);
        }
        cur *= ifac[i];
        ans += cur;
    }

    PRINTLN(ans);

    EXIT();
}
