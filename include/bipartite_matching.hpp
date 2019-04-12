// bipartite_matching {{{

// 2部グラフの最大マッチング
//
// g は隣接リスト表現
// (k,match) を返す
// k: 最大マッチングのペア数
// match: 各頂点とペアになる頂点
tuple<i64,vector<i64>> bipartite_matching(const vector<vector<i64>>& g) {
    i64 n = SIZE(g);
    vector<i64> match(n, -1);

    BoolArray visited(n);
    auto dfs = FIX([&g,&match,&visited](auto self, i64 v) -> bool {
        visited[v] = true;
        for(i64 to : g[v]) {
            i64 w = match[to];
            if(w == -1 || (!visited[w] && self(w))) {
                match[v]  = to;
                match[to] = v;
                return true;
            }
        }
        return false;
    });

    i64 k = 0;
    REP(v, n) {
        if(match[v] != -1) continue;
        ALL(fill, visited, false);
        if(dfs(v))
            ++k;
    }

    return make_tuple(k, match);
}

// }}}
