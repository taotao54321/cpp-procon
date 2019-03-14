#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N; RD(N);
    vector<Vector> ps; RD(ps, N);
    Polygon poly(ps);

    f64 ans = poly.area();

    cout << fixed << setprecision(1);
    PRINTLN(ans);

    return 0;
}
