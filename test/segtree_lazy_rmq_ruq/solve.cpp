#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N; RD(N);
    i64 Q; RD(Q);

    using Monoid = i64;  // 区間の最小値
    using Action = i64;  // 区間を更新する値
    auto seg = make_segtree_lazy<Monoid,Action>(
        /* fm= */ [](Monoid m1, Monoid m2) { return MIN(m1,m2); },
        /* fa= */ [](Monoid, Action a) { return a; },
        /* fl= */ [](Action, Action a) { return a; },
        /* unity_monoid= */ INF,
        /* unity_action= */ INF,
        /* n= */ N,
        /* x= */ BIT_I_1(31)
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
