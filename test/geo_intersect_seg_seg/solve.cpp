#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 Q = RD();
    REP(_, Q) {
        auto p0 = RD<Vector>();
        auto p1 = RD<Vector>();
        auto p2 = RD<Vector>();
        auto p3 = RD<Vector>();
        bool ans = geo_intersect(Segment(p0,p1), Segment(p2,p3));
        PRINTLN(ans ? 1 : 0);
    }

    EXIT();
}
