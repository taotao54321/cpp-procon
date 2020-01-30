#include "procon.hpp"
#include "num.hpp"

signed main() {
    decltype(auto) prime = is_prime_table<1299710>();

    for(;;) {
        i64 K = RD();
        if(K == 0) break;

        if(prime[K]) {
            PRINTLN(0);
            continue;
        }

        i64 l = K;
        i64 r = K;
        while(!prime[l]) --l;
        while(!prime[r]) ++r;
        i64 ans = r - l;

        PRINTLN(ans);
    }

    EXIT();
}
