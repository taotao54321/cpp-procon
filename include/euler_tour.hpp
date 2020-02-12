// euler_tour {{{

auto euler_tour(const vector<vector<Int>>& g, Int root) {
    Int n = SIZE(g);
    vector<Int> ls(n);
    vector<Int> rs(n);

    Int i = 0;
    auto dfs = FIX([&](auto&& self, Int v, Int p) -> void {
        ls[v] = i++;
        for(Int to : g[v]) {
            if(to == p) continue;
            self(to, v);
        }
        rs[v] = i;
    });
    dfs(root, -1);

    return make_pair(ls, rs);
}

// }}}
