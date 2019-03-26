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

    vector<i64> articulations;
    tie(articulations,ignore) = graph_lowlink(G);

    ALL(sort, articulations);

    ALL(for_each, articulations, GENERIC(PRINTLN));

    EXIT();
}
