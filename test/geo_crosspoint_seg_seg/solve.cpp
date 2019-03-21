#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 Q; RD(Q);
    REP(_, Q) {
        Vector p0; RD(p0);
        Vector p1; RD(p1);
        Segment seg1(p0,p1);
        Vector p2; RD(p2);
        Vector p3; RD(p3);
        Segment seg2(p2,p3);

        Vector ans = geo_crosspoint(seg1, seg2);
        PRINTLN(ans.x, ans.y);
    }

    EXIT();
}
