#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 a = RD();
    i64 b = RD();

    i64 x,y; tie(ignore,x,y) = extgcd(a,b);

    PRINTLN(x, y);

    EXIT();
}
