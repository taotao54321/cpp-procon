#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N = RD();
    auto ps = RD_ARRAY<Vector>(N);
    Polygon poly(ps);

    i64 Q = RD();
    REP(_, Q) {
        auto p = RD<Vector>();

        Containment ans = poly.containment(p);

        switch(ans) {
        case CONT_IN:  PRINTLN(2); break;
        case CONT_ON:  PRINTLN(1); break;
        case CONT_OUT: PRINTLN(0); break;
        default: ASSERT(false);
        }
    }

    EXIT();
}
