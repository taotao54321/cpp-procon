#include "procon.hpp"
#include "container.hpp"
#include "graph.hpp"

signed main() {
    i64 N; RD(N);
    i64 M; RD(M);

    vector<vector<pair<i64,i64>>> G(N);
    REP(_, M) {
        i64 from,to; RD(from); RD(to); --from; --to;  // 0-based
        i64 cost; RD(cost);
        G[from].emplace_back(to,cost);
        G[to].emplace_back(from,cost);
    }

    vector<i64> d;
    vector<i64> parent;
    tie(d,parent) = graph_dijkstra(G, N-1);

    vector<i64> route;
    for(i64 v = 0; v != -1; v = parent[v]) {
        route.emplace_back(v+1);  // 1-based
    }

    if(route.back() == N)
        PRINTLN(route);
    else
        PRINTLN(-1);

    EXIT();
}
