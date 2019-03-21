#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    Vector c1; f64 r1; RD(c1); RD(r1);
    Circle cir1(c1,r1);
    Vector c2; f64 r2; RD(c2); RD(r2);
    Circle cir2(c2,r2);

    vector<Vector> ans = geo_crosspoints(cir1, cir2);
    ALL(sort, ans, ON(less<>(), [](const Vector& p) { return make_pair(p.x,p.y); }));
    PRINTLN(ans[0].x, ans[0].y, ans[1].x, ans[1].y);

    EXIT();
}
