// prufer {{{

// 木を対応する prufer code にエンコード
//
// O(n)
//
// g: 隣接リスト表現(頂点数 n >= 2)
// 長さ n-2 の prufer code を返す
vector<Int> prufer_from_tree(const vector<vector<Int>>& g) {
    Int n = SIZE(g);
    ASSERT(n >= 2);

    vector<Int> parent(n, -1);
    auto dfs = FIX([&g,&parent](auto&& self, Int v) -> void {
        for(Int to : g[v]) {
            if(to == parent[v]) continue;
            parent[to] = v;
            self(to);
        }
    });
    dfs(n-1);

    vector<Int> deg(n);
    Int ptr = -1;
    REP(v, n) {
        deg[v] = SIZE(g[v]);
        if(deg[v] == 1 && ptr == -1)
            ptr = v;
    }

    vector<Int> prufer(n-2);
    Int leaf = ptr;
    REP(i, n-2) {
        Int p = parent[leaf];
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
vector<pair<Int,Int>> prufer_to_tree(const vector<Int>& prufer) {
    Int n = SIZE(prufer) + 2;
    ASSERT(n >= 2);

    vector<Int> deg(n, 1);
    for(Int v : prufer)
        ++deg[v];

    Int ptr = 0;
    while(deg[ptr] != 1)
        ++ptr;

    vector<pair<Int,Int>> es;
    es.reserve(n-1);
    Int leaf = ptr;
    for(Int v : prufer) {
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
