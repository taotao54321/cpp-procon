#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N = RD();
    auto ps = RD_ARRAY<Vector>(N);
    Polygon convex(ps);

    i64 Q = RD();
    REP(_, Q) {
        auto p1 = RD<Vector>();
        auto p2 = RD<Vector>();
        Line line(p1,p2);

        Polygon cut = geo_convex_cut(convex, line);
        f64 ans = cut.area();

        PRINTLN(ans);
    }

    EXIT();
}
