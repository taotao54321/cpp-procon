#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N = RD();
    i64 K = RD();

    decltype(auto) dp = partition_count_table<2001,1001>();
    ModP ans = dp[N+K][K];

    PRINTLN(ans);

    EXIT();
}
