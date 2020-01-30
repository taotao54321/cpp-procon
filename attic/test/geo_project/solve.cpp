#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    auto p1 = RD<Vector>();
    auto p2 = RD<Vector>();
    Line line(p1,p2);

    i64 Q = RD();
    REP(_, Q) {
        auto p = RD<Vector>();
        Vector ans = geo_project(line, p);
        PRINTLN(ans.x, ans.y);
    }

    EXIT();
}
