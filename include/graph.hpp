// graph (container が必要) {{{

template<typename T>
vector<vector<pair<i64,T>>> graph_make_weighted(i64 n) {
    return vector<vector<pair<i64,T>>>(n);
}

vector<vector<i64>> graph_make_unweighted(i64 n) {
    return vector<vector<i64>>(n);
}

// n 頂点の初期化済み隣接行列 g を返す
//
// g[i][j]: i==j なら 0, i!=j なら INF
template<typename T>
vector<vector<T>> graph_make_matrix(i64 n) {
    vector<vector<T>> g(n, vector<T>(n, PROCON_INF<T>()));
    REP(i, n) {
        g[i][i] = T(0);
    }
    return g;
}

// ダイクストラ法
//
// (d,parent) を返す
// d[i]: start から点 i への最短距離(到達不能な点は INF)
// parent[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
template<typename T>
tuple<vector<T>,vector<i64>> graph_dijkstra(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<T> d(n, PROCON_INF<T>());
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

    return make_tuple(d, parent);
}

// ベルマンフォード法
//
// 負閉路が存在する場合、最短距離が負の無限大になる点が生じる。
// そのような点を全て検出するため、2*n 回ループしている
// (一般的な実装の倍の回数。ただし更新がなくなったら打ち切る)
//
// (d,parent) を返す
// d[i]: start から点 i への最短距離(到達不能なら INF, 負の無限大なら -INF)
// parent[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
template<typename T>
tuple<vector<T>,vector<i64>> graph_bellman(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<T> d(n, PROCON_INF<T>());
    vector<i64> parent(n, -1);

    d[start] = T(0);

    REP(i, 2*n) {
        bool update = false;
        REP(from, n) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
            if(d[from] == PROCON_INF<T>()) continue;
            for(const auto& p : g[from]) {
                i64 to,cost; tie(to,cost) = p;
                i64 d_new = d[from] == -PROCON_INF<T>() ? -PROCON_INF<T>() : d[from] + cost;
                if(d_new < d[to]) {
                    update     = true;
                    d[to]      = i >= n-1 ? -PROCON_INF<T>() : d_new;
                    parent[to] = from;
                }
            }
#pragma GCC diagnostic pop
        }
        if(!update) break;
    }

    return make_tuple(d, parent);
}

// SPFA (Shortest Path Faster Algorithm)
//
// 理論上はベルマンフォードより速いはずだが、実際はそうでもなさげ
// 最短距離が負の無限大になる点を全て検出するため 2*n 回ループしている
// (一般的な実装の倍の回数。ただし更新がなくなったら打ち切る)
//
// (d,parent) を返す
// d[i]: start から点 i への最短距離(到達不能なら INF, 負の無限大なら -INF)
// parent[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
template<typename T>
tuple<vector<T>,vector<i64>> graph_spfa(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<T> d(n, PROCON_INF<T>());
    vector<i64> parent(n, -1);

    queue<i64> que;
    BoolArray in_que(n, false);
    const auto enqueue = [&que,&in_que](i64 v) { que.emplace(v); in_que[v] = true; };
    const auto dequeue = [&que,&in_que]() { i64 v = POP(que); in_que[v] = false; return v; };

    d[start] = T(0);
    enqueue(start);

    REP(i, 2*n) {
        REP(_, que.size()) {
            i64 from = dequeue();
            for(const auto& p : g[from]) {
                i64 to,cost; tie(to,cost) = p;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
                i64 d_new = d[from] == -PROCON_INF<T>() ? -PROCON_INF<T>() : d[from] + cost;
                if(d_new < d[to]) {
                    d[to]      = i >= n-1 ? -PROCON_INF<T>() : d_new;
                    parent[to] = from;
                    if(!in_que[to]) enqueue(to);
                }
#pragma GCC diagnostic pop
            }
        }
        if(que.empty()) break;
    }

    return make_tuple(d, parent);
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
tuple<bool,vector<vector<i64>>> graph_floyd(vector<vector<T>>& g) {
    i64 n = SIZE(g);
    vector<vector<i64>> nex(n, vector<i64>(n,-1));

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
    REP(i, n) REP(j, n) {
        if(g[i][j] != PROCON_INF<T>())
            nex[i][j] = j;
    }

    REP(k, n) {
        REP(i, n) {
            if(g[i][k] == PROCON_INF<T>()) continue;
            REP(j, n) {
                if(g[k][j] == PROCON_INF<T>()) continue;
                if(chmin(g[i][j], g[i][k] + g[k][j])) {
                    nex[i][j] = nex[i][k];
                }
                if(i == j && g[i][j] < 0) return make_tuple(false, nex);
            }
        }
    }
#pragma GCC diagnostic pop

    return make_tuple(true, nex);
}

// TODO: 重みあり/なし両対応
// (関節点リスト,橋リスト) を返す
tuple<vector<i64>,vector<pair<i64,i64>>> graph_lowlink(const vector<vector<i64>>& g) {
    i64 n = SIZE(g);
    vector<i64> ord(n, -1);
    vector<i64> low(n, -1);

    vector<i64>           articulations;
    vector<pair<i64,i64>> bridges;

    auto dfs = FIX([&g,&ord,&low,&articulations,&bridges](auto&& self, i64 v, i64 parent, i64 k) -> void {
        low[v] = ord[v] = k;

        bool arti = false;
        i64 n_child = 0;
        for(i64 to : g[v]) {
            // 親または後退辺
            if(ord[to] != -1) {
                if(to != parent)
                    chmin(low[v], ord[to]);
                continue;
            }

            // 子を辿り、low[v] を更新
            ++n_child;
            self(to, v, k+1);
            chmin(low[v], low[to]);

            // 関節点判定(根でない場合)
            if(parent != -1 && low[to] >= ord[v])
                arti = true;

            // 橋判定
            if(low[to] > ord[v])
                bridges.emplace_back(minmax(v,to));
        }
        // 関節点判定(根の場合)
        if(parent == -1 && n_child > 1)
            arti = true;

        if(arti)
            articulations.emplace_back(v);
    });
    dfs(0, -1, 0);

    return make_tuple(articulations, bridges);
}

// 各頂点の (indegree,outdegree) のリストを返す (隣接リスト版)
vector<pair<i64,i64>> graph_degrees_list(const vector<vector<i64>>& g) {
    i64 n = SIZE(g);
    vector<pair<i64,i64>> res(n, {0,0});

    REP(from, n) {
        for(i64 to : g[from]) {
            ++SND(res[from]);
            ++FST(res[to]);
        }
    }

    return res;
}

// 各頂点の (indegree,outdegree) のリストを返す (隣接行列版)
vector<pair<i64,i64>> graph_degrees_matrix(const vector<vector<i64>>& g) {
    i64 n = SIZE(g);
    vector<pair<i64,i64>> res(n, {0,0});

    REP(from, n) REP(to, n) {
        i64 k = g[from][to];
        SND(res[from]) += k;
        FST(res[to])   += k;
    }

    return res;
}

// グラフのオイラー路 (隣接リスト版)
//
// g は破壊される
// start: 始点
// digraph: 有向グラフか?
vector<i64> graph_euler_trail_list(vector<vector<i64>>& g, i64 start, bool digraph) {
    // スタックオーバーフロー回避のため再帰を使わず自前の stack で処理
    enum Action { CALL, RESUME };

    vector<i64> res;

    stack<tuple<Action,i64>> stk;
    stk.emplace(CALL, start);
    while(!stk.empty()) {
        Action act; i64 v; tie(act,v) = POP(stk);
        switch(act) {
        case CALL:
            stk.emplace(RESUME, v);
            while(!g[v].empty()) {
                i64 to = POP_BACK(g[v]);
                if(!digraph)
                    g[to].erase(ALL(find, g[to], v));
                stk.emplace(CALL, to);
            }
            break;
        case RESUME:
            res.emplace_back(v);
            break;
        }
    }

    ALL(reverse, res);

    return res;
}

// 無向グラフのオイラー路 (隣接行列版)
//
// g[v][w]: v,w 間の辺の本数 (破壊される)
// start: 始点
// digraph: 有向グラフか?
vector<i64> graph_euler_trail_matrix(vector<vector<i64>>& g, i64 start, bool digraph) {
    // スタックオーバーフロー回避のため再帰を使わず自前の stack で処理
    enum Action { CALL, RESUME };

    i64 n = SIZE(g);
    vector<i64> res;

    stack<tuple<Action,i64>> stk;
    stk.emplace(CALL, start);
    while(!stk.empty()) {
        Action act; i64 v; tie(act,v) = POP(stk);
        switch(act) {
        case CALL:
            stk.emplace(RESUME, v);
            REP(to, n) {
                if(g[v][to] == 0) continue;
                --g[v][to];
                if(!digraph)
                    --g[to][v];
                stk.emplace(CALL, to);
            }
            break;
        case RESUME:
            res.emplace_back(v);
            break;
        }
    }

    ALL(reverse, res);

    return res;
}

// }}}
