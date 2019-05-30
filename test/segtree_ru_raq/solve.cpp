#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N; RD(N);
    i64 Q; RD(Q);

    using T = i64;  // 区間に一様に加算する値
    auto seg = make_segtree_ru<T>(
        /* f= */ [](const T& a1, const T& a2) { return a1 + a2; },
        /* unity= */ 0,
        /* n= */ N
    );

    REP(_, Q) {
        i64 cmd; RD(cmd);
        if(cmd == 0) {
            i64 s,t; RD1(s); RD1(t);
            i64 x; RD(x);
            seg.update(s, t-s+1, x);
        }
        else if(cmd == 1) {
            i64 i; RD1(i);
            i64 ans = seg.query(i);
            PRINTLN(ans);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
