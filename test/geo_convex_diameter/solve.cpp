#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N = RD();
    auto ps = RD_ARRAY<Vector>(N);
    Polygon convex(ps);

    f64 d2; tie(d2,ignore,ignore) = geo_convex_diameter_sq(convex);
    f64 ans = sqrt(d2);

    PRINTLN(ans);

    EXIT();
}
