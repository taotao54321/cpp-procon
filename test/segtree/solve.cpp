#include "procon.hpp"
#include "monoid.hpp"
#include "segtree.hpp"

signed main() {
    i64 N; RD(N);
    i64 Q; RD(Q);

    SegTree<i64,plus<>> segtree(N, 0);
    REP(_, Q) {
        i64 cmd; RD(cmd);
        if(cmd == 0) {
            i64 i; RD1(i);
            i64 x; RD(x);
            segtree.add(i, x);
        }
        else if(cmd == 1) {
            i64 s,t; RD1(s); RD1(t);
            ASSERT(s <= t);
            i64 n = t-s+1;
            i64 ans = segtree.query(s, n);
            PRINTLN(ans);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
