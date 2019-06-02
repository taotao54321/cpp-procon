#include "procon.hpp"
#include "graph.hpp"

signed main() {
    i64 N = RD();
    i64 M = RD();
    i64 start = RD();

    vector<vector<pair<i64,i64>>> G(N);
    REP(_, M) {
        i64 from = RD();
        i64 to   = RD();
        i64 cost = RD();
        G[from].emplace_back(to,cost);
    }

    vector<i64> d;
    tie(d,ignore) = graph_spfa(G, start);

    if(ALL(find, d, -INF) != end(d)) {
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
