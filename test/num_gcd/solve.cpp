#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 x, y; RD(x); RD(y);

    i64 ans = gcd(x,y);

    PRINTLN(ans);

    EXIT();
}
