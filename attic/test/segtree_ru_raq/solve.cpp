#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N = RD();
    i64 Q = RD();

    auto seg = segtree_ru_make<i64,i64>(
        [](i64 val, i64 a) { return val+a; },
        [](i64 al, i64 ar) { return al+ar; },
        0,
        N
    );
    LOOP(Q) {
        i64 cmd = RD();
        if(cmd == 0) {
            i64 s = RD1();
            i64 t = RD1(); ++t;
            i64 x = RD();
            seg.act(s, t, x);
        }
        else if(cmd == 1) {
            i64 i = RD1();
            i64 ans = seg.query(i);
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }

    EXIT();
}
