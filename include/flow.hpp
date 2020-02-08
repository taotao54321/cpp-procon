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
tuple<Int,vector<vector<Int>>> flow_fulkerson(vector<vector<Int>>& g, Int s, Int t) {
    Int n = SIZE(g);
    vector<vector<Int>> flow(n, vector<Int>(n,0));

    BoolArray visited(n);
    auto dfs = FIX([&g,t,n,&flow,&visited](auto&& self, Int v, Int f) -> Int {
        if(v == t) return f;

        visited[v] = true;
        REP(to, n) {
            if(visited[to]) continue;
            if(g[v][to] == 0) continue;
            Int f2 = self(to, min(f,g[v][to]));
            if(f2 > 0) {
                Int res = f2;
                g[v][to] -= f2;
                g[to][v] += f2;
                Int d = min(flow[to][v], f2);
                flow[to][v] -= d;
                f2          -= d;
                flow[v][to] += f2;
                return res;
            }
        }
        return 0;
    });

    Int res = 0;
    for(;;) {
        ALL(fill, visited, false);
        Int f = dfs(s, INF);
        if(f == 0) break;
        res += f;
    }

    return make_tuple(res, flow);
}

// }}}
