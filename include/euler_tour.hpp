// euler_tour {{{

auto euler_tour_vertex(const vector<vector<Int>>& g, Int root) {
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

template<class T>
auto euler_tour_edge(const vector<vector<pair<Int,T>>>& g, Int root) {
    Int n = SIZE(g);
    vector<Int> ds(n);
    vector<Int> us(n);
    vector<T> ws(2*n);

    Int i = 0;
    auto dfs = FIX([&](auto&& self, Int v, Int p, Int w) -> void {
        ws[i] = w;
        ds[v] = i++;
        for(const auto& e : g[v]) {
            Int to; T ww; tie(to,ww) = e;
            if(to == p) continue;
            self(to, v, ww);
        }
        ws[i] = -w;
        us[v] = i++;
    });
    dfs(root, -1, 0);

    return make_tuple(ds, us, ws);
}

// }}}
