#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    f64 x1,y1; RD(x1); RD(y1);
    f64 x2,y2; RD(x2); RD(y2);
    Line line(x1,y1,x2,y2);

    i64 Q; RD(Q);
    REP(_, Q) {
        f64 x,y; RD(x); RD(y);
        Vector p(x,y);
        Vector ans = geo_project(line, p);
        PRINTLN(ans.x, ans.y);
    }
}
