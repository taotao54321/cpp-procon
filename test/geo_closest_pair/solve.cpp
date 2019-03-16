#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N; RD(N);
    vector<Vector> ps; RD(ps, N);

    auto t = geo_closest_pair_sq(ps);
    f64 ans = sqrt(get<0>(t));

    PRINTLN(ans);

    return 0;
}
