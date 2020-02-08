// gen (random, string, prufer が必要) {{{

// ランダムな文字列を生成
//
// n: 長さ
// chars: 文字種
template<typename Engine>
string gen_string(RngT<Engine>& rng, Int n, const string& chars) {
    string res;
    res.reserve(n);
    REP(_, n) {
        res.push_back(*ALL(rng.choose, chars));
    }
    return res;
}

// ランダムな木を生成
//
// n: 頂点数(n >= 2)
// 辺のリストを返す
template<typename Engine>
vector<pair<Int,Int>> gen_tree(RngT<Engine>& rng, Int n) {
    vector<Int> prufer(n-2);
    ALL(rng.generate, prufer, 0, n-1);

    return prufer_to_tree(prufer);
}

// ランダムな連結単純無向グラフを生成
//
// n: 頂点数 (n >= 2)
// m: 辺数 (n-1 <= m <= n*(n-1)/2)
// 辺のリストを返す
template<typename Engine>
vector<pair<Int,Int>> gen_connected_graph(RngT<Engine>& rng, Int n, Int m) {
    ASSERT(n >= 2);
    ASSERT(n-1 <= m && m <= n*(n-1)/2);

    set<pair<Int,Int>> es;
    {
        vector<pair<Int,Int>> ev = gen_tree(rng, n);
        for(auto& e : ev) {
            if(e.first > e.second)
                swap(e.first, e.second);
        }
        ALL(es.insert, ev);
    }

    REP(_, m-SIZE(es)) {
        Int s = -1;
        Int t = -1;
        while(s == t || es.find(make_pair(s,t)) != end(es)) {
            s = rng.uniform(0, n-1);
            t = rng.uniform(0, n-1);
            if(s > t) swap(s,t);
        }
        es.emplace(s,t);
    }

    return vector<pair<Int,Int>>(begin(es), end(es));
}

// ランダムな連結単純無向重み付きグラフを生成
//
// n: 頂点数 (n >= 2)
// m: 辺数 (n-1 <= m <= n*(n-1)/2)
// cmin: 重み下限
// cmax: 重み上限
// 辺のリストを返す
template<typename Engine>
vector<tuple<Int,Int,Int>> gen_connected_graph_weighted(
    RngT<Engine>& rng, Int n, Int m, Int cmin, Int cmax)
{
    ASSERT(cmin <= cmax);

    auto es = gen_connected_graph(rng, n, m);

    vector<tuple<Int,Int,Int>> res;
    res.reserve(SIZE(es));
    for(const auto& e : es) {
        Int c = rng.uniform(cmin, cmax);
        res.emplace_back(e.first, e.second, c);
    }

    return res;
}

// }}}
