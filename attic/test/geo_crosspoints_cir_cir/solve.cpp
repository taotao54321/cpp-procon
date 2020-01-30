#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    auto c1 = RD<Vector>();
    auto r1 = RD<f64>();
    Circle cir1(c1,r1);
    auto c2 = RD<Vector>();
    auto r2 = RD<f64>();
    Circle cir2(c2,r2);

    vector<Vector> ans = geo_crosspoints(cir1, cir2);
    ALL(sort, ans, ON(less<>(), [](const Vector& p) { return make_pair(p.x,p.y); }));
    PRINTLN(ans[0].x, ans[0].y, ans[1].x, ans[1].y);

    EXIT();
}
