#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N = RD();
    auto ps = RD_ARRAY<Vector>(N);

    Polygon ans = geo_convex_hull(move(ps));

    PRINTLN(SIZE(ans.ps));
    for(const Vector& p : ans.ps) {
        i64 x = static_cast<i64>(p.x);
        i64 y = static_cast<i64>(p.y);
        PRINTLN(x, y);
    }

    EXIT();
}
