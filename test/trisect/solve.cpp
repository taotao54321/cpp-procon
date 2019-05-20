#include "procon.hpp"
#include "trisect.hpp"

template<typename T>
T f(T x) {
    // 頂点 (2,2)
    return -x*x + 4*x - 2;
}

signed main() {
    {
        i64 x = trisect_max_integer(-100, 100, f<i64>);
        ASSERT(x == 2);
    }
    {
        f64 x = trisect_max_real(-100.0, 100.0, f<f64>);
        ASSERT(feq(x, 2.0, 1e-5));
    }

    EXIT();
}
