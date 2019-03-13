#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 Q; RD(Q);
    REP(_, Q) {
        Vector p0; RD(p0);
        Vector p1; RD(p1);
        Vector p2; RD(p2);
        Vector p3; RD(p3);
        bool ans = geo_intersect(p0,p1,p2,p3);
        PRINTLN(ans ? 1 : 0);
    }
}
