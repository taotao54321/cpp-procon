#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    Vector c; RD(c);
    f64 r; RD(r);
    Circle cir(c,r);

    i64 Q; RD(Q);
    REP(_, Q) {
        Vector p1; RD(p1);
        Vector p2; RD(p2);
        Line line(p1,p2);

        vector<Vector> ans = geo_crosspoints(cir, line);
        ALL(sort, ans, ON(less<>(), [](const Vector& p) { return make_pair(p.x,p.y); }));

        PRINTLN(ans[0].x, ans[0].y, ans[1].x, ans[1].y);
    }

    return 0;
}
