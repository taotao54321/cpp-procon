#include "procon.hpp"
#include "container.hpp"
#include "graph.hpp"

signed main() {
    i64 N = RD();
    i64 M = RD();
    i64 S = RD();

    auto G = graph_make_weighted<i64>(N);
    REP(_, M) {
        i64 from = RD();
        i64 to   = RD();
        i64 cost = RD();
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
