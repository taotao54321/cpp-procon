#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    auto c = RD<Vector>();
    auto r = RD<f64>();
    Circle cir(c,r);

    i64 Q = RD();
    REP(_, Q) {
        auto p1 = RD<Vector>();
        auto p2 = RD<Vector>();
        Line line(p1,p2);

        vector<Vector> ans = geo_crosspoints(cir, line);
        ALL(sort, ans, ON(less<>(), [](const Vector& p) { return make_pair(p.x,p.y); }));

        PRINTLN(ans[0].x, ans[0].y, ans[1].x, ans[1].y);
    }

    EXIT();
}
