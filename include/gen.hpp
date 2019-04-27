// gen (random, string, prufer が必要) {{{

// ランダムな文字列を生成
//
// n: 長さ
// chars: 文字種
template<typename Engine>
string gen_string(RngT<Engine>& rng, i64 n, const string& chars) {
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
vector<pair<i64,i64>> gen_tree(RngT<Engine>& rng, i64 n) {
    vector<i64> prufer(n-2);
    ALL(rng.generate, prufer, 0, n-1);

    return prufer_to_tree(prufer);
}

// }}}
