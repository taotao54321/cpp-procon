#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N,K; RD(N); RD(K);

    decltype(auto) dp = partition_count_table<2001,1001>();
    ModP ans = dp[N+K][K];

    PRINTLN(ans);

    EXIT();
}
