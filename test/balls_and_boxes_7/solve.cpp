#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N,K; RD(N); RD(K);

    decltype(auto) fac  = factorial<1001>();
    decltype(auto) ifac = ifactorial<1001>();

    ModP ans = 0;
    FOR(i, 1, K+1) {
        ModP cur = 0;
        FOR(j, 0, i+1) {
            i64 sign = is_even(j) ? 1 : -1;
            cur += sign * combination_count(i,j,fac,ifac) * pow_binary(ModP(i-j),N);
        }
        cur *= ifac[i];
        ans += cur;
    }

    PRINTLN(ans);

    return 0;
}
