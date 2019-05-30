#include "procon.hpp"
#include "container.hpp"
#include "graph.hpp"

signed main() {
    i64 N = RD();
    i64 M = RD();

    auto G = graph_make_matrix<i64>(N);
    REP(i, N) {
        G[i][i] = 0;
    }
    REP(_, M) {
        i64 from = RD();
        i64 to   = RD();
        i64 cost = RD();
        G[from][to] = cost;
    }

    bool ok;
    tie(ok,ignore) = graph_floyd(G);
    if(!ok) {
        PRINTLN("NEGATIVE CYCLE");
        EXIT();
    }

    REP(i, N) {
        REP(j, N) {
            if(G[i][j] == INF)
                PRINT("INF");
            else
                PRINT(G[i][j]);
            if(j != N-1) PRINT(' ');
        }
        PRINTLN();
    }

    EXIT();
}
