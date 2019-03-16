#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    i64 N; RD(N);
    vector<Vector> ps; RD(ps, N);
    Polygon convex(ps);

    i64 Q; RD(Q);
    REP(_, Q) {
        Vector p1,p2; RD(p1); RD(p2);
        Line line(p1,p2);

        Polygon cut = geo_convex_cut(convex, line);
        f64 ans = cut.area();

        PRINTLN(ans);
    }

    return 0;
}
