#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 Q = RD();
    REP(_, Q) {
        auto p0 = RD<Vector>();
        auto p1 = RD<Vector>();
        Segment seg1(p0,p1);
        auto p2 = RD<Vector>();
        auto p3 = RD<Vector>();
        Segment seg2(p2,p3);

        f64 ans = geo_distance(seg1, seg2);
        PRINTLN(ans);
    }

    EXIT();
}
