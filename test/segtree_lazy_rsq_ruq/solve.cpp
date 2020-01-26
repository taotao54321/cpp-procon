#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N = RD();
    i64 Q = RD();

    using Monoid = pair<i64,i64>;  // 区間の (総和,幅)
    using Action = i64;            // 区間を更新する値
    auto seg = make_segtree_lazy<Monoid,Action>(
        /* fm= */ [](const Monoid& m1, const Monoid& m2) {
            return Monoid(m1.first+m2.first, m1.second+m2.second);
        },
        /* fa= */ [](const Monoid& m, Action a) {
            return Monoid(a*m.second, m.second);
        },
        /* fl= */ [](Action, Action a) { return a; },
        /* unity_monoid= */ Monoid(0,1),
        /* unity_action= */ INF,
        /* n= */ N
    );

    REP(_, Q) {
        i64 cmd = RD();
        if(cmd == 0) {
            i64 s = RD();
            i64 t = RD();
            i64 x = RD();
            seg.update(s, t-s+1, x);
        }
        else if(cmd == 1) {
            i64 s = RD();
            i64 t = RD();
            i64 ans = seg.query(s, t-s+1).first;
            PRINTLN(ans);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
