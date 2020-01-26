#include "procon.hpp"
#include "graph.hpp"

[[noreturn]] void impossible() {
    PRINTLN("NO");
    EXIT();
}

signed main() {
    i64 N = RD();
    i64 M = RD();

    auto G = vec_make<i64>(N,N, 0);
    i64 v_any = -1;
    REP(_, M) {
        i64 s = RD();
        i64 t = RD();
        ++G[s][t];
        ++G[t][s];
        v_any = s;
    }

    auto degs = graph_degrees_matrix(G);
    i64 cnt = 0;
    vector<i64> odds;
    REP(i, N) {
        i64 d = degs[i].first;
        if(d > 0)
            ++cnt;
        if(is_odd(d))
            odds.emplace_back(i);
    }
    if(!odds.empty() && SIZE(odds) != 2) impossible();

    i64 s;
    if(SIZE(odds) == 2) {
        s = odds.front();
    }
    else {
        s = v_any;
    }
    auto trail = graph_euler_trail_matrix(G, s, false);

    ALL(sort, trail);
    UNIQ(trail);
    if(SIZE(trail) != cnt) impossible();

    PRINTLN("YES");

    EXIT();
}
