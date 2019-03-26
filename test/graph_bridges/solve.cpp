#include "procon.hpp"
#include "container.hpp"
#include "graph.hpp"

signed main() {
    i64 N; RD(N);
    i64 M; RD(M);

    auto G = graph_make_unweighted(N);
    REP(_, M) {
        i64 s,t; RD(s); RD(t);
        G[s].emplace_back(t);
        G[t].emplace_back(s);
    }

    vector<pair<i64,i64>> bridges;
    tie(ignore,bridges) = graph_lowlink(G);

    ALL(sort, bridges);

    ALL(for_each, bridges, GENERIC(PRINTLN));

    EXIT();
}
