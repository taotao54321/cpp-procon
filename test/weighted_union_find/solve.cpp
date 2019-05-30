#include "procon.hpp"
#include "union_find.hpp"

enum {
    CMD_RELATE = 0,
    CMD_DIFF   = 1,
};

signed main() {
    i64 N = RD();
    i64 Q = RD();

    WeightedUnionFind wuf(N);
    REP(_, Q) {
        i64 cmd = RD();
        if(cmd == CMD_RELATE) {
            i64 x = RD();
            i64 y = RD();
            i64 z = RD();
            if(!wuf.unite(x, y, z))
                ASSERT(false);
        }
        else if(cmd == CMD_DIFF) {
            i64 x = RD();
            i64 y = RD();
            i64 rx = wuf.root(x);
            i64 ry = wuf.root(y);
            if(rx != ry) {
                PRINTLN("?");
            }
            else {
                i64 ans = wuf.weight(y) - wuf.weight(x);
                PRINTLN(ans);
            }
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
