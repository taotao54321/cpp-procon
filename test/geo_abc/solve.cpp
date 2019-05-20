#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    f64 x0,y0; RD(x0); RD(y0);
    f64 x1,y1; RD(x1); RD(y1);
    Vector p0(x0,y0);
    Vector p1(x1,y1);

    i64 Q; RD(Q);
    REP(_, Q) {
        f64 x2,y2; RD(x2); RD(y2);
        Vector p2(x2,y2);
        ABC ans = geo_abc(p0,p1,p2);
        switch(ans) {
        case ABC_CCW:        PRINTLN("COUNTER_CLOCKWISE"); break;
        case ABC_CW:         PRINTLN("CLOCKWISE");         break;
        case ABC_ON_BACK:    PRINTLN("ONLINE_BACK");       break;
        case ABC_ON_FRONT:   PRINTLN("ONLINE_FRONT");      break;
        case ABC_ON_SEGMENT: PRINTLN("ON_SEGMENT");        break;
        default: ASSERT(false);
        }
    }

    EXIT();
}
