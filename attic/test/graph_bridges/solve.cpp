#include "procon.hpp"
#include "graph.hpp"

signed main() {
    i64 N = RD();
    i64 M = RD();

    auto G = graph_make_unweighted(N);
    REP(_, M) {
        i64 s = RD();
        i64 t = RD();
        G[s].emplace_back(t);
        G[t].emplace_back(s);
    }

    vector<pair<i64,i64>> bridges;
    tie(ignore,bridges) = graph_lowlink(G);

    ALL(sort, bridges);

    ALL(for_each, bridges, LIFT(PRINTLN));

    EXIT();
}
