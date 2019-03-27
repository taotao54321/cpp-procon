#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N; RD(N);

    REP(_, N) {
        u64 X; RD(X);
        bool ans = is_prime_u64(X);
        PRINTLN(X, ans);
    }

    EXIT();
}
