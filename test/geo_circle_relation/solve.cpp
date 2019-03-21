#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    Vector c1; f64 r1; RD(c1); RD(r1);
    Circle cir1(c1,r1);
    Vector c2; f64 r2; RD(c2); RD(r2);
    Circle cir2(c2,r2);

    CircleRelation ans = geo_circle_relation(cir1, cir2);

    PRINTLN(ans);

    EXIT();
}
