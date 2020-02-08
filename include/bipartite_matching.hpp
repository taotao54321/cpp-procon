// bipartite_matching {{{

// 2部グラフの最大マッチング
//
// g は隣接リスト表現
// (k,match) を返す
// k: 最大マッチングのペア数
// match: 各頂点とペアになる頂点
tuple<Int,vector<Int>> bipartite_matching(const vector<vector<Int>>& g) {
    Int n = SIZE(g);
    vector<Int> match(n, -1);

    BoolArray visited(n);
    auto dfs = FIX([&g,&match,&visited](auto&& self, Int v) -> bool {
        visited[v] = true;
        for(Int to : g[v]) {
            Int w = match[to];
            if(w == -1 || (!visited[w] && self(w))) {
                match[v]  = to;
                match[to] = v;
                return true;
            }
        }
        return false;
    });

    Int k = 0;
    REP(v, n) {
        if(match[v] != -1) continue;
        ALL(fill, visited, false);
        if(dfs(v))
            ++k;
    }

    return make_tuple(k, match);
}

// }}}
