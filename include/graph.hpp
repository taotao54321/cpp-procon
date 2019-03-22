// {{{ graph (container が必要)

// ダイクストラ法
//
// (d,parent) を返す
// d[i]: start から点 i への最短距離(到達不能な点は INF)
// parent[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
pair<vector<i64>,vector<i64>> graph_dijkstra(const vector<vector<pair<i64,i64>>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<i64> d(n, INF);
    vector<i64> parent(n, -1);

    BoolArray done(n, false);
    MinHeap<pair<i64,i64>> que;

    d[start] = 0;
    que.emplace(0, start);

    i64 n_remain = n;
    while(!que.empty()) {
        i64 dmin,vmin; tie(dmin,vmin) = POP(que);

        if(d[vmin] < dmin) continue;

        done[vmin] = true;
        if(--n_remain == 0) break;

        for(const auto& p : g[vmin]) {
            i64 to,cost; tie(to,cost) = p;
            if(done[to]) continue;

            i64 d_new = dmin + cost;
            if(d_new < d[to]) {
                d[to] = d_new;
                parent[to] = vmin;
                que.emplace(d_new, to);
            }
        }
    }

    return { d, parent };
}

// ベルマンフォード法
//
// (ok,d,parent) を返す
// ok: 負閉路が存在しない場合に限り true
// d[i]: start から点 i への最短距離(到達不能な点は INF, 負閉路上の点は -INF)
// parent[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
tuple<bool,vector<i64>,vector<i64>> graph_bellman(const vector<vector<pair<i64,i64>>>& g, i64 start) {
    i64 n = SIZE(g);
    bool ok = true;
    vector<i64> d(n, INF);
    vector<i64> parent(n, -1);

    d[start] = 0;

    REP(i, n) {
        bool update = false;
        REP(from, n) {
            if(d[from] == INF) continue;
            for(const auto& p : g[from]) {
                i64 to,cost; tie(to,cost) = p;
                i64 d_new = d[from] + cost;
                if(d_new < d[to]) {
                    update = true;
                    d[to] = i == n-1 ? -INF : d_new;
                    parent[to] = from;
                }
            }
        }
        if(!update) break;
        if(i == n-1) ok = false;
    }

    return make_tuple(ok, d, parent);
}

// ワーシャルフロイド法
//
// g は隣接行列 (g[from][to]) で、from == to の場合 0, from != to で辺
// がない場合 INF
//
// g は全点対間最短距離で上書きされる
// (ok,nex) を返す
// ok: 負閉路が存在しない場合に限り true
// nex[i][j]: i から j へ最短経路で行くとき、次に辿るべき点
pair<bool,vector<vector<i64>>> graph_floyd(vector<vector<i64>>& g) {
    i64 n = SIZE(g);
    vector<vector<i64>> nex(n, vector<i64>(n,-1));
    REP(i, n) REP(j, n) {
        if(g[i][j] != INF)
            nex[i][j] = j;
    }

    REP(k, n) {
        REP(i, n) {
            if(g[i][k] == INF) continue;
            REP(j, n) {
                if(g[k][j] == INF) continue;
                if(chmin(g[i][j], g[i][k] + g[k][j])) {
                    nex[i][j] = nex[i][k];
                }
                if(i == j && g[i][j] < 0) return { false, nex };
            }
        }
    }

    return { true, nex };
}

// }}}
