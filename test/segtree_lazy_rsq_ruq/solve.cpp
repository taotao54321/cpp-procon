#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N; RD(N);
    i64 Q; RD(Q);

    using Monoid = pair<i64,i64>;  // 区間の (総和,幅)
    using Action = i64;            // 区間を更新する値
    auto seg = make_segtree_lazy<Monoid,Action>(
        /* fm= */ [](const Monoid& m1, const Monoid& m2) {
            return Monoid(FST(m1)+FST(m2), SND(m1)+SND(m2));
        },
        /* fa= */ [](const Monoid& m, Action a) {
            return Monoid(a*SND(m), SND(m));
        },
        /* fl= */ [](Action, Action a) { return a; },
        /* unity_monoid= */ Monoid(0,1),
        /* unity_action= */ INF,
        /* n= */ N
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
            i64 ans = FST(seg.query(s, t-s+1));
            PRINTLN(ans);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
