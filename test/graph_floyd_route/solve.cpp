#include "procon.hpp"
#include "container.hpp"
#include "graph.hpp"

struct Pos {
    i64 x, y;
};

void solve(i64 N) {
    vector<Pos> ps(N);
    REP(_, N) {
        i64 b; RD(b); --b;  // 0-based
        i64 x,y; RD(x); RD(y);
        ps[b] = { x, y };
    }

    vector<vector<f64>> G(N, vector<f64>(N, FINF));
    REP(i, N) REP(j, N) {
        const Pos& p1 = ps[i];
        const Pos& p2 = ps[j];
        i64 d_sq = ipow(p1.x-p2.x,2) + ipow(p1.y-p2.y,2);
        if(d_sq <= 2500) {
            G[i][j] = G[j][i] = sqrt(d_sq);
        }
    }

    bool ok;
    vector<vector<i64>> nex;
    tie(ok,nex) = graph_floyd(G);
    assert(ok);

    i64 M; RD(M);
    REP(_, M) {
        i64 s,g; RD(s); RD(g); --s; --g;  // 0-based
        if(nex[s][g] == -1) {
            PRINTLN("NA");
            continue;
        }

        vector<i64> route;
        for(i64 v = s; v != g; v = nex[v][g]) {
            route.emplace_back(v);
        }
        route.emplace_back(g);

        ALL(transform_self, route, [](i64 e) { return e+1; });  // 1-based
        PRINTLN(route);
    }
}

signed main() {
    for(;;) {
        i64 N; RD(N);
        if(N == 0) break;
        solve(N);
    }

    EXIT();
}
