#include "procon.hpp"
#include "geometry.hpp"

signed main() {
    auto c1 = RD<Vector>();
    auto r1 = RD<f64>();
    Circle cir1(c1,r1);
    auto c2 = RD<Vector>();
    auto r2 = RD<f64>();
    Circle cir2(c2,r2);

    CircleRelation ans = geo_circle_relation(cir1, cir2);

    PRINTLN(ans);

    EXIT();
}
