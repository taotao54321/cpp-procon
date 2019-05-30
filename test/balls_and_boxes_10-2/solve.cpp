#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N = RD();
    i64 K = RD();

    auto f = partition_count_func<2001,1001>();
    ModP ans = f(N+K,K);

    PRINTLN(ans);

    EXIT();
}
