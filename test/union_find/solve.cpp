#include "procon.hpp"
#include "union_find.hpp"

enum {
    CMD_UNITE = 0,
    CMD_SAME  = 1,
};

signed main() {
    i64 N; RD(N);
    i64 Q; RD(Q);

    UnionFind uf(N);
    REP(_, Q) {
        i64 cmd,x,y; RD(cmd); RD(x); RD(y);
        if(cmd == CMD_UNITE) {
            uf.unite(x,y);
        }
        else if(cmd == CMD_SAME) {
            bool same = uf.root(x) == uf.root(y);
            PRINTLN(same ? 1 : 0);
        }
        else {
            assert(false);
        }
    }

    EXIT();
}
