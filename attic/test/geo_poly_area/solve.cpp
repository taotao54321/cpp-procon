#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N = RD();
    auto ps = RD_ARRAY<Vector>(N);
    Polygon poly(ps);

    f64 ans = poly.area();

    cout << fixed << setprecision(1);
    PRINTLN(ans);

    EXIT();
}
