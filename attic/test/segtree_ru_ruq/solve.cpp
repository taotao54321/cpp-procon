#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N = RD();
    i64 Q = RD();

    auto seg = segtree_ru_make<i64,i64>(
        [](i64, i64 a) { return a; },
        [](i64, i64 a) { return a; },
        INF,
        N,
        BIT_I_1(31)
    );

    LOOP(Q) {
        i64 cmd = RD();
        if(cmd == 0) {
            i64 s = RD();
            i64 t = RD(); ++t;
            i64 x = RD();
            seg.act(s, t, x);
        }
        else if(cmd == 1) {
            i64 i = RD();
            i64 ans = seg.query(i);
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }

    EXIT();
}
