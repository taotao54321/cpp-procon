#include "procon.hpp"
#include "container.hpp"
#include "graph.hpp"

signed main() {
    i64 N; RD(N);
    i64 M; RD(M);
    i64 S; RD(S);

    vector<vector<pair<i64,i64>>> G(N);
    REP(_, M) {
        i64 from,to; RD(from); RD(to);
        i64 cost; RD(cost);
        G[from].emplace_back(to,cost);
    }

    vector<i64> d;
    tie(d,ignore) = graph_dijkstra(G, S);

    REP(i, N) {
        if(d[i] == INF)
            PRINTLN("INF");
        else
            PRINTLN(d[i]);
    }

    EXIT();
}
