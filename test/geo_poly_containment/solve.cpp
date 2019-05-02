#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N; RD(N);
    auto ps = RD_ARRAY<Vector>(N);
    Polygon poly(ps);

    i64 Q; RD(Q);
    REP(_, Q) {
        Vector p; RD(p);

        Containment ans = poly.containment(p);

        switch(ans) {
        case CONT_IN:  PRINTLN(2); break;
        case CONT_ON:  PRINTLN(1); break;
        case CONT_OUT: PRINTLN(0); break;
        default: assert(false);
        }
    }

    EXIT();
}
