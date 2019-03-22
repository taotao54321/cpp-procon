#include "procon.hpp"
#include "container.hpp"
#include "graph.hpp"

signed main() {
    i64 N; RD(N);
    i64 M; RD(M);
    i64 start; RD(start);

    vector<vector<pair<i64,i64>>> G(N);
    REP(_, M) {
        i64 from,to; RD(from); RD(to);
        i64 cost; RD(cost);
        G[from].emplace_back(to,cost);
    }

    bool ok;
    vector<i64> d;
    tie(ok,d,ignore) = graph_spfa(G, start);

    if(!ok) {
        PRINTLN("NEGATIVE CYCLE");
        EXIT();
    }

    REP(i, N) {
        if(d[i] == INF)
            PRINTLN("INF");
        else
            PRINTLN(d[i]);
    }

    EXIT();
}
