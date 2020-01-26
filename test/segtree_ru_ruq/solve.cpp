#include "procon.hpp"
#include "segtree.hpp"
#include "serial.hpp"

signed main() {
    i64 N = RD();
    i64 Q = RD();

    // 値の変更は順序について非可換だが、タイムスタンプを付けることで
    // 可換にできる
    using T = pair<i64,i64>;  // (タイムスタンプ,値)
    auto seg = make_segtree_ru<T>(
        /* f= */ [](const T& a1, const T& a2) { return MAX(a1,a2); },
        /* unity= */ T(-INF,0),
        /* n= */ N,
        /* x= */ T(-1,BIT_I_1(31))
    );

    Serial serial(0);
    REP(_, Q) {
        i64 cmd = RD();
        if(cmd == 0) {
            i64 s = RD();
            i64 t = RD();
            i64 x = RD();
            seg.update(s, t-s+1, {serial.next(),x});
        }
        else if(cmd == 1) {
            i64 i = RD();
            i64 ans = seg.query(i).second;
            PRINTLN(ans);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
