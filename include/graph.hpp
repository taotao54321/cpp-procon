// {{{ graph (container が必要)

// ダイクストラ法
//
// (d,parent) を返す
// d[i]: start から点 i への最短距離(到達不能な点は INF)
// parent[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
template<typename T>
pair<vector<T>,vector<i64>> graph_dijkstra(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<T> d(n, PROCON_INF<T>);
    vector<i64> parent(n, -1);

    BoolArray done(n, false);
    MinHeap<pair<T,i64>> que;

    d[start] = T(0);
    que.emplace(T(0), start);

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
template<typename T>
tuple<bool,vector<T>,vector<i64>> graph_bellman(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    bool ok = true;
    vector<T> d(n, PROCON_INF<T>);
    vector<i64> parent(n, -1);

    d[start] = T(0);

    REP(i, n) {
        bool update = false;
        REP(from, n) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
            if(d[from] == PROCON_INF<T>) continue;
#pragma GCC diagnostic pop
            for(const auto& p : g[from]) {
                i64 to,cost; tie(to,cost) = p;
                i64 d_new = d[from] + cost;
                if(d_new < d[to]) {
                    update = true;
                    d[to] = i == n-1 ? -PROCON_INF<T> : d_new;
                    parent[to] = from;
                }
            }
        }
        if(!update) break;
        if(i == n-1) ok = false;
    }

    return make_tuple(ok, d, parent);
}

// SPFA (Shortest Path Faster Algorithm)
//
// ベルマンフォードより速い、はず
//
// (ok,d,parent) を返す
// ok: 負閉路が存在しない場合に限り true
// d[i]: start から点 i への最短距離(到達不能な点は INF, 負閉路上の点は -INF)
// parent[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
template<typename T>
tuple<bool,vector<T>,vector<i64>> graph_spfa(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    bool ok = true;
    vector<T> d(n, PROCON_INF<T>);
    vector<i64> parent(n, -1);

    queue<i64> que;
    BoolArray in_que(n, false);
    const auto enqueue = [&que,&in_que](i64 v) { que.emplace(v); in_que[v] = true; };
    const auto dequeue = [&que,&in_que]() { i64 v = POP(que); in_que[v] = false; return v; };

    d[start] = T(0);
    enqueue(start);

    REP(i, n) {
        REP(_, que.size()) {
            i64 from = dequeue();
            for(const auto& p : g[from]) {
                i64 to,cost; tie(to,cost) = p;
                i64 d_new = d[from] + cost;
                if(d_new < d[to]) {
                    d[to] = i == n-1 ? -PROCON_INF<T> : d_new;
                    parent[to] = from;
                    if(!in_que[to]) enqueue(to);
                }
            }
        }
        if(que.empty()) break;
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
// nex[i][j]: i から j へ最短経路で行くとき、次に辿るべき点(到達不能なら -1)
template<typename T>
pair<bool,vector<vector<i64>>> graph_floyd(vector<vector<T>>& g) {
    i64 n = SIZE(g);
    vector<vector<i64>> nex(n, vector<i64>(n,-1));

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
    REP(i, n) REP(j, n) {
        if(g[i][j] != PROCON_INF<T>)
            nex[i][j] = j;
    }

    REP(k, n) {
        REP(i, n) {
            if(g[i][k] == PROCON_INF<T>) continue;
            REP(j, n) {
                if(g[k][j] == PROCON_INF<T>) continue;
                if(chmin(g[i][j], g[i][k] + g[k][j])) {
                    nex[i][j] = nex[i][k];
                }
                if(i == j && g[i][j] < 0) return { false, nex };
            }
        }
    }
#pragma GCC diagnostic pop

    return { true, nex };
}

// }}}
