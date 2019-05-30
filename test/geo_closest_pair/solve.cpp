#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N = RD();
    auto ps = RD_ARRAY<Vector>(N);

    auto t = geo_closest_pair_sq(ps);
    f64 ans = sqrt(get<0>(t));

    PRINTLN(ans);

    EXIT();
}
