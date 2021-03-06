#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    auto p = RD<Vector>();
    auto c = RD<Vector>();
    auto r = RD<f64>();
    Circle cir(c, r);

    vector<Line> ans = geo_tangent(cir, p);
    ALL(sort, ans, LT_ON([](const Line& line) {
        const Vector& q = line.p2;
        return make_pair(q.x, q.y);
    }));

    for(const Line& line : ans) {
        const Vector& q = line.p2;
        PRINTLN(q.x, q.y);
    }

    EXIT();
}
