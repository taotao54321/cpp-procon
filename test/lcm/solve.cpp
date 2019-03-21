#include "procon.hpp"
#include "num.hpp"

i64 N;
vector<i64> A;

signed main() {
    RD(N);
    RD(A, N);

    i64 ans = ALL(accumulate, A, 1, lcm);

    PRINTLN(ans);

    EXIT();
}
