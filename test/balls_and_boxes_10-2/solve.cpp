#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N,K; RD(N); RD(K);

    auto f = partition_count_func<2001,1001>();
    ModP ans = f(N+K,K);

    PRINTLN(ans);

    EXIT();
}
