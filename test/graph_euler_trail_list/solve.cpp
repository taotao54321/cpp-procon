#include "procon.hpp"
#include "graph.hpp"

[[noreturn]] void impossible() {
    PRINTLN("NO");
    EXIT();
}

signed main() {
    i64 N = RD();
    i64 M = RD();

    vector<vector<i64>> G(N);
    i64 v_any = -1;
    REP(_, M) {
        i64 s = RD();
        i64 t = RD();
        G[s].emplace_back(t);
        G[t].emplace_back(s);
        v_any = s;
    }

    auto degs = graph_degrees_list(G);
    i64 cnt = 0;
    vector<i64> odds;
    REP(i, N) {
        i64 d = FST(degs[i]);
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
    auto trail = graph_euler_trail_list(G, s, false);

    ALL(sort, trail);
    UNIQ(trail);
    if(SIZE(trail) != cnt) impossible();

    PRINTLN("YES");

    EXIT();
}
