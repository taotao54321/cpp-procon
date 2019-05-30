#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N = RD();
    i64 Q = RD();

    using T = i64;  // 区間に一様に加算する値
    auto seg = make_segtree_ru<T>(
        /* f= */ [](const T& a1, const T& a2) { return a1 + a2; },
        /* unity= */ 0,
        /* n= */ N
    );

    REP(_, Q) {
        i64 cmd = RD();
        if(cmd == 0) {
            i64 s = RD1();
            i64 t = RD1();
            i64 x = RD();
            seg.update(s, t-s+1, x);
        }
        else if(cmd == 1) {
            i64 i = RD1();
            i64 ans = seg.query(i);
            PRINTLN(ans);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
