#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    auto p0 = RD<Vector>();
    auto p1 = RD<Vector>();

    i64 Q = RD();
    REP(_, Q) {
        auto p2 = RD<Vector>();
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
