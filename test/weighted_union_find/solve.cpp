#include "procon.hpp"
#include "union_find.hpp"

enum {
    CMD_RELATE = 0,
    CMD_DIFF   = 1,
};

signed main() {
    i64 N; RD(N);
    i64 Q; RD(Q);

    WeightedUnionFind wuf(N);
    REP(_, Q) {
        i64 cmd; RD(cmd);
        if(cmd == CMD_RELATE) {
            i64 x,y,z; RD(x); RD(y); RD(z);
            if(!wuf.unite(x, y, z))
                assert(false);
        }
        else if(cmd == CMD_DIFF) {
            i64 x,y; RD(x); RD(y);
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
            assert(false);
        }
    }

    EXIT();
}
