#include "procon.hpp"
#include "union_find.hpp"

enum {
    CMD_UNITE = 0,
    CMD_SAME  = 1,
};

signed main() {
    i64 N = RD();
    i64 Q = RD();

    UnionFind uf(N);
    REP(_, Q) {
        i64 cmd = RD();
        i64 x   = RD();
        i64 y   = RD();
        if(cmd == CMD_UNITE) {
            uf.unite(x,y);
        }
        else if(cmd == CMD_SAME) {
            bool same = uf.root(x) == uf.root(y);
            PRINTLN(same ? 1 : 0);
        }
        else {
            ASSERT(false);
        }
    }

    EXIT();
}
