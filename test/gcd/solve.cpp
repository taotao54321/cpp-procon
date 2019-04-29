#include "procon.hpp"

signed main() {
    i64 x, y; RD(x); RD(y);

    i64 ans = GCD(x,y);

    PRINTLN(ans);

    EXIT();
}
