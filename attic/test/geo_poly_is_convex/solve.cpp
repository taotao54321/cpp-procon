#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N = RD();
    auto ps = RD_ARRAY<Vector>(N);
    Polygon poly(ps);

    bool ans = poly.is_convex();

    PRINTLN(ans ? 1 : 0);

    EXIT();
}
