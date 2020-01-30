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

    vector<i64> articulations;
    tie(articulations,ignore) = graph_lowlink(G);

    ALL(sort, articulations);

    ALL(for_each, articulations, LIFT(PRINTLN));

    EXIT();
}
