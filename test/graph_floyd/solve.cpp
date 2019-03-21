#include "procon.hpp"
#include "container.hpp"
#include "graph.hpp"

signed main() {
    i64 N; RD(N);
    i64 M; RD(M);

    vector<vector<i64>> G(N, vector<i64>(N, INF));
    REP(i, N) {
        G[i][i] = 0;
    }
    REP(_, M) {
        i64 from,to; RD(from); RD(to);
        i64 cost; RD(cost);
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
