// graph {{{

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

// 辺のリストから n 頂点無向グラフの隣接リスト表現を得る
vector<vector<i64>> graph_from_edges(i64 n, const vector<pair<i64,i64>>& es) {
    vector<vector<i64>> g(n);
    for(const auto& e : es) {
        i64 s,t; tie(s,t) = e;
        g[s].emplace_back(t);
        g[t].emplace_back(s);
    }
    return g;
}

// 単純無向グラフが木かどうか判定する
//
// g: 隣接リスト表現(頂点数 n > 0)
bool graph_is_tree(const vector<vector<i64>>& g) {
    i64 n = SIZE(g);
    ASSERT(n > 0);

    i64 edge_cnt = 0;
    vector<bool> visited(n, false);
    auto dfs = FIX([&g,&edge_cnt,&visited](auto&& self, i64 v) -> void {
        visited[v] = true;
        for(i64 to : g[v]) {
            if(visited[to]) continue;
            ++edge_cnt;
            self(to);
        }
    });
    dfs(0);

    bool connected = ALL(all_of, visited, [](bool b) { return b; });

    return edge_cnt == n-1 && connected;
}

// BFSで重みなしグラフ上の単一始点最短経路を求める
//
// (ds,ps) を返す
// ds[i]: start から点 i への最短距離(到達不能な点は INF)
// ps[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
tuple<vector<i64>,vector<i64>> graph_bfs(const vector<vector<i64>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<i64> ds(n, INF);
    vector<i64> ps(n, -1);

    queue<i64> que;
    que.emplace(start);
    ds[start] = 0;

    while(!que.empty()) {
        i64 v = POP(que);

        for(i64 to : g[v]) {
            if(ds[to] != INF) continue;
            que.emplace(to);
            ds[to] = ds[v] + 1;
            ps[to] = v;
        }
    }

    return make_tuple(ds, ps);
}

// ダイクストラ法
//
// (ds,ps) を返す
// ds[i]: start から点 i への最短距離(到達不能な点は PROCON_INF<T>())
// ps[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
template<typename T>
tuple<vector<T>,vector<i64>> graph_dijkstra(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<T> ds(n, PROCON_INF<T>());
    vector<i64> ps(n, -1);

    auto que = priority_queue_make<pair<T,i64>>(greater<>{});

    ds[start] = T{};
    que.emplace(T{}, start);

    i64 n_remain = n;
    while(!que.empty()) {
        T d; i64 v; tie(d,v) = POP(que);
        if(ds[v] < d) continue;

        if(--n_remain == 0) break;

        for(const auto& p : g[v]) {
            i64 to; T cost; tie(to,cost) = p;

            T d_new = d + cost;
            if(chmin(ds[to], d_new)) {
                ps[to] = v;
                que.emplace(d_new, to);
            }
        }
    }

    return make_tuple(ds, ps);
}

// 辺のコストが小さい非負整数の場合の最良優先探索(01-BFS の一般化)
// 全ての辺のコストは [0,k] であること
//
// (ds,ps) を返す
// ds[i]: start から点 i への最短距離(到達不能な点は INF)
// ps[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
tuple<vector<i64>,vector<i64>> graph_k_bfs(const vector<vector<pair<i64,i64>>>& g, i64 k, i64 start) {
    i64 n = SIZE(g);
    vector<i64> ds(n, INF);
    vector<i64> ps(n, -1);

    vector<queue<i64>> ques(k+1);
    auto enqueue = [&ques](i64 to, i64 cost) {
        ques[cost].emplace(to);
    };
    auto dequeue = [&ques]() -> i64 {
        for(auto& que : ques)
            if(!que.empty())
                return POP(que);
        return -1;
    };

    enqueue(start, 0);
    ds[start] = 0;

    i64 v;
    while((v = dequeue()) != -1) {
        for(const auto& p : g[v]) {
            i64 to,cost; tie(to,cost) = p;

            i64 d_new = ds[v] + cost;
            if(chmin(ds[to], d_new)) {
                ps[to] = v;
                enqueue(to, cost);
            }
        }
    }

    return make_tuple(ds, ps);
}

// ベルマンフォード法
//
// 負閉路が存在する場合、最短距離が負の無限大になる点が生じる。
// そのような点を全て検出するため、2*n 回ループしている
// (一般的な実装の倍の回数。ただし更新がなくなったら打ち切る)
//
// (ds,ps) を返す
// ds[i]: start から点 i への最短距離(到達不能なら INF, 負の無限大なら -INF)
// ps[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
template<typename T>
tuple<vector<T>,vector<i64>> graph_bellman(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<T> ds(n, PROCON_INF<T>());
    vector<i64> ps(n, -1);

    ds[start] = T{};

    REP(i, 2*n) {
        bool update = false;
        REP(from, n) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
            if(ds[from] == PROCON_INF<T>()) continue;
            for(const auto& p : g[from]) {
                i64 to; T cost; tie(to,cost) = p;
                T d_new = ds[from]==-PROCON_INF<T>() ? -PROCON_INF<T>() : ds[from]+cost;
                if(d_new < ds[to]) {
                    update = true;
                    ds[to] = i >= n-1 ? -PROCON_INF<T>() : d_new;
                    ps[to] = from;
                }
            }
#pragma GCC diagnostic pop
        }
        if(!update) break;
    }

    return make_tuple(ds, ps);
}

// SPFA (Shortest Path Faster Algorithm)
//
// 理論上はベルマンフォードより速いはずだが、実際はそうでもなさげ
// 最短距離が負の無限大になる点を全て検出するため 2*n 回ループしている
// (一般的な実装の倍の回数。ただし更新がなくなったら打ち切る)
//
// (ds,ps) を返す
// ds[i]: start から点 i への最短距離(到達不能なら INF, 負の無限大なら -INF)
// ps[i]: 最短経路木における点 i の親(start および到達不能な点は -1)
template<typename T>
tuple<vector<T>,vector<i64>> graph_spfa(const vector<vector<pair<i64,T>>>& g, i64 start) {
    i64 n = SIZE(g);
    vector<T> ds(n, PROCON_INF<T>());
    vector<i64> ps(n, -1);

    queue<i64> que;
    vector<bool> in_que(n, false);
    const auto enqueue = [&que,&in_que](i64 v) { que.emplace(v); in_que[v] = true; };
    const auto dequeue = [&que,&in_que]() { i64 v = POP(que); in_que[v] = false; return v; };

    ds[start] = T{};
    enqueue(start);

    REP(i, 2*n) {
        REP(_, que.size()) {
            i64 from = dequeue();
            for(const auto& p : g[from]) {
                i64 to; T cost; tie(to,cost) = p;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
                T d_new = ds[from]==-PROCON_INF<T>() ? -PROCON_INF<T>() : ds[from]+cost;
                if(d_new < ds[to]) {
                    ds[to] = i >= n-1 ? -PROCON_INF<T>() : d_new;
                    ps[to] = from;
                    if(!in_que[to]) enqueue(to);
                }
#pragma GCC diagnostic pop
            }
        }
        if(que.empty()) break;
    }

    return make_tuple(ds, ps);
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
// トポロジカルソート
// queue を MinHeap に変えると辞書順最小のものが求まる
//
// (ok,res) を返す
// ok: DAGであったかどうか
// res: 結果
tuple<bool,vector<i64>> graph_tsort(const vector<vector<i64>>& g) {
    i64 n = SIZE(g);
    vector<i64> res;
    res.reserve(n);

    vector<i64> deg_in(n, 0);
    for(const auto& tos : g)
        for(auto to : tos)
            ++deg_in[to];

    queue<i64> que;
    REP(v, n) {
        if(deg_in[v] == 0)
            que.emplace(v);
    }

    while(!que.empty()) {
        i64 v = POP(que);

        res.emplace_back(v);

        for(auto to : g[v]) {
            if(--deg_in[to] > 0) continue;
            que.emplace(to);
        }
    }

    bool ok = SIZE(res) == n;
    return make_tuple(ok, res);
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
            ++res[from].second;
            ++res[to].first;
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
        res[from].second += k;
        res[to].first    += k;
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
                i64 to = g[v].back(); g[v].pop_back();
                if(!digraph)
                    g[to].erase(ALL(find, g[to], v));
                stk.emplace(CALL, to);
            }
            break;
        case RESUME:
            res.emplace_back(v);
            break;
        default: ASSERT(false);
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
        default: ASSERT(false);
        }
    }

    ALL(reverse, res);

    return res;
}

// }}}
