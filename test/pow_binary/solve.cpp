#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 M,N; RD(M); RD(N);

    ModP m(M);
    ModP ans = pow_binary(m, N);

    PRINTLN(ans);

    return 0;
}
