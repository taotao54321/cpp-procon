#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 a, b; RD(a); RD(b);

    i64 x,y; tie(ignore,x,y) = extgcd(a,b);

    PRINT(x);
    PRINT(' ');
    PRINTLN(y);

    return 0;
}
