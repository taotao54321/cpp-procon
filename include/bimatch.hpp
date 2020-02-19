// bimatch {{{

pair<Int,vector<Int>> bimatch(const vector<vector<Int>>& g) {
    Int n = SIZE(g);

    vector<Int> match(n, -1);
    Int ts = 0;
    vector<Int> tss(n, ts);  // timestamp

    auto dfs = FIX([&](auto&& self, Int v) -> bool {
        tss[v] = ts;
        for(Int to : g[v]) {
            Int w = match[to];
            if(w < 0 || (tss[w] < ts && self(w))) {
                match[v]  = to;
                match[to] = v;
                return true;
            }
        }
        return false;
    });

    Int cnt = 0;
    REP(v, n) {
        if(match[v] >= 0) continue;
        ++ts;
        if(dfs(v))
            ++cnt;
    }

    return {cnt, match};
}

// }}}
