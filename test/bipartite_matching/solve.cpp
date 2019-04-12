#include "procon.hpp"
#include "bipartite_matching.hpp"

signed main() {
    i64 X; RD(X);
    i64 Y; RD(Y);
    i64 M; RD(M);

    vector<vector<i64>> G(X+Y);
    REP(_, M) {
        i64 x,y; RD(x); RD(y); y += X;  // 番号を振り直す
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }

    i64 k;
    vector<i64> match;
    tie(k,match) = bipartite_matching(G);

    i64 k2 = ALL(count_if, match, [](i64 e) { return e != -1; });
    assert(is_even(k2));
    assert(k == k2 / 2);

    PRINTLN(k);

    EXIT();
}
