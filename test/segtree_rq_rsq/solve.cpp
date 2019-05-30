#include "procon.hpp"
#include "segtree.hpp"

signed main() {
    i64 N; RD(N);
    i64 Q; RD(Q);

    using Monoid = pair<i64,i64>;  // 区間の (総和,幅)
    using Action = i64;            // 区間に一様に加える値
    auto seg = make_segtree_rq<Monoid,Action>(
        /* fm= */ [](const Monoid& m1, const Monoid& m2) {
            return Monoid(FST(m1)+FST(m2), SND(m1)+SND(m2));
        },
        /* fa= */ [](const Monoid& m, Action a) {
            return Monoid(FST(m)+a*SND(m), SND(m));
        },
        /* unity_monoid= */ Monoid(0,1),
        /* n= */ N
    );

    REP(_, Q) {
        i64 cmd; RD(cmd);
        if(cmd == 0) {
            i64 i; RD1(i);
            i64 x; RD(x);
            seg.update(i, x);
        }
        else if(cmd == 1) {
            i64 s,t; RD1(s); RD1(t);
            i64 ans = FST(seg.query(s, t-s+1));
            PRINTLN(ans);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
