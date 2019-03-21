// {{{ graph (container が必要)

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
