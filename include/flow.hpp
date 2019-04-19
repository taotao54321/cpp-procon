// flow {{{

// Ford-Fulkerson 法
//
// g は辺の容量を表す行列 (g[from][to])
// s は始点、t は終点
//
// g は残余グラフで上書きされる
// (f,flow) を返す
// f: s-t フローの最大値
// flow[from][to]: from から to への流量
tuple<i64,vector<vector<i64>>> flow_fulkerson(vector<vector<i64>>& g, i64 s, i64 t) {
    i64 n = SIZE(g);
    vector<vector<i64>> flow(n, vector<i64>(n,0));

    BoolArray visited(n);
    auto dfs = FIX([&g,t,n,&flow,&visited](auto&& self, i64 v, i64 f) -> i64 {
        if(v == t) return f;

        visited[v] = true;
        REP(to, n) {
            if(visited[to]) continue;
            if(g[v][to] == 0) continue;
            i64 f2 = self(to, min(f,g[v][to]));
            if(f2 > 0) {
                i64 res = f2;
                g[v][to] -= f2;
                g[to][v] += f2;
                i64 d = min(flow[to][v], f2);
                flow[to][v] -= d;
                f2          -= d;
                flow[v][to] += f2;
                return res;
            }
        }
        return 0;
    });

    i64 res = 0;
    for(;;) {
        ALL(fill, visited, false);
        i64 f = dfs(s, INF);
        if(f == 0) break;
        res += f;
    }

    return make_tuple(res, flow);
}

// }}}
