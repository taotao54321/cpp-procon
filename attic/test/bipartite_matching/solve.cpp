#include "procon.hpp"
#include "bipartite_matching.hpp"

signed main() {
    i64 X = RD();
    i64 Y = RD();
    i64 M = RD();

    vector<vector<i64>> G(X+Y);
    REP(_, M) {
        i64 x = RD();
        i64 y = RD(); y += X;  // 番号を振り直す
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }

    i64 k;
    vector<i64> match;
    tie(k,match) = bipartite_matching(G);

    i64 k2 = ALL(count_if, match, [](i64 e) { return e != -1; });
    ASSERT(is_even(k2));
    ASSERT(k == k2 / 2);

    PRINTLN(k);

    EXIT();
}
