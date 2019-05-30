#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N = RD();

    REP(_, N) {
        u64 X = RD<u64>();
        bool ans = is_prime_u64(X);
        PRINTLN(X, ans);
    }

    EXIT();
}
