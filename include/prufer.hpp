// prufer {{{

// 木を対応する prufer code にエンコード
//
// O(n)
//
// g: 隣接リスト表現(頂点数 n >= 2)
// 長さ n-2 の prufer code を返す
vector<i64> prufer_from_tree(const vector<vector<i64>>& g) {
    i64 n = SIZE(g);
    ASSERT(n >= 2);

    vector<i64> parent(n, -1);
    auto dfs = FIX([&g,&parent](auto&& self, i64 v) -> void {
        for(i64 to : g[v]) {
            if(to == parent[v]) continue;
            parent[to] = v;
            self(to);
        }
    });
    dfs(n-1);

    vector<i64> deg(n);
    i64 ptr = -1;
    REP(v, n) {
        deg[v] = SIZE(g[v]);
        if(deg[v] == 1 && ptr == -1)
            ptr = v;
    }

    vector<i64> prufer(n-2);
    i64 leaf = ptr;
    REP(i, n-2) {
        i64 p = parent[leaf];
        prufer[i] = p;
        --deg[p];

        if(deg[p] == 1 && p < ptr) {
            leaf = p;
        }
        else {
            do {
                ++ptr;
            } while(deg[ptr] != 1);
            leaf = ptr;
        }
    }

    return prufer;
}

// prufer code をデコードし、対応する木を得る
//
// O(n)
//
// prufer: 長さ n-2 の prufer code (n:頂点数、n >= 2)
// n-1 個の辺を返す
vector<pair<i64,i64>> prufer_to_tree(const vector<i64>& prufer) {
    i64 n = SIZE(prufer) + 2;
    ASSERT(n >= 2);

    vector<i64> deg(n, 1);
    for(i64 v : prufer)
        ++deg[v];

    i64 ptr = 0;
    while(deg[ptr] != 1)
        ++ptr;

    vector<pair<i64,i64>> es;
    es.reserve(n-1);
    i64 leaf = ptr;
    for(i64 v : prufer) {
        es.emplace_back(leaf, v);
        --deg[v];

        if(deg[v] == 1 && v < ptr) {
            leaf = v;
        }
        else {
            do {
                ++ptr;
            } while(deg[ptr] != 1);
            leaf = ptr;
        }
    }
    es.emplace_back(leaf, n-1);

    return es;
}

// }}}
