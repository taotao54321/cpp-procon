#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N; RD(N);
    i64 Q; RD(Q);

    using Monoid = i64;  // 区間の最小値
    using Action = i64;  // 区間に一様に加える値
    auto seg = make_segtree_lazy<Monoid,Action>(
        /* fm= */ [](Monoid m1, Monoid m2) { return MIN(m1,m2); },
        /* fa= */ [](Monoid m, Action a) { return m + a; },
        /* fl= */ [](Action a1, Action a2) { return a1 + a2; },
        /* unity_monoid= */ INF,
        /* unity_action= */ 0,
        /* n= */ N,
        /* x= */ 0
    );

    REP(_, Q) {
        i64 cmd; RD(cmd);
        if(cmd == 0) {
            i64 s,t; RD(s); RD(t);
            i64 x; RD(x);
            seg.update(s, t-s+1, x);
        }
        else if(cmd == 1) {
            i64 s,t; RD(s); RD(t);
            i64 ans = seg.query(s, t-s+1);
            PRINTLN(ans);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
