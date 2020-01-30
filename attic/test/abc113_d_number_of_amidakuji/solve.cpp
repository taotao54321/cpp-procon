#include "procon.hpp"
#include "matrix.hpp"
#include "num.hpp"

signed main() {
    i64 H = RD();
    i64 W = RD();
    i64 K = RD1();

    decltype(auto) fib = fibonacci_table<1000>();
    ASSERT(SIZE(fib) == 1000);

    auto m = Matrix<ModInt>::zeros(W);
    // 左
    FOR(i, 1, W) {
        m.at(i-1,i) = fib[i] * fib[W-i];
    }
    // 右
    FOR(i, 0, W-1) {
        m.at(i+1,i) = fib[i+1] * fib[W-i-1];
    }
    // まっすぐ
    FOR(i, 0, W) {
        m.at(i,i) = fib[i+1] * fib[W-i];
    }

    m = m.pow(H);

    // 行列を見れば事足りるが、ベクトルとの乗算のverify用に
    vector<ModInt> dp(W, 0);
    dp[0] = 1;
    vector<ModInt> v = m * dp;

    ModInt ans = v[K];

    PRINTLN(ans);

    EXIT();
}
