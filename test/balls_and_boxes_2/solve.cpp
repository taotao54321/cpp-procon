#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N,K; RD(N); RD(K);

    decltype(auto) fac  = factorial<1001>();
    decltype(auto) ifac = ifactorial<1001>();

    ModP ans = permutation_count(K, N, fac, ifac);

    PRINTLN(ans);

    return 0;
}
