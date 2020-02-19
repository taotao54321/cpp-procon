// flow {{{

struct FlowEdge {
    Int to;
    Int cap;
    Int rev;
    FlowEdge(Int t, Int c, Int r) : to(t), cap(c), rev(r) {}
};

void flow_add_edge(vector<vector<FlowEdge>>& g, Int from, Int to, Int cap) {
    g[from].emplace_back(to, cap, SIZE(g[to]));
    g[to].emplace_back(from, 0, SIZE(g[from])-1);
}

Int flow_ford_fulkerson(vector<vector<FlowEdge>>& g, Int s, Int t) {
    Int n = SIZE(g);

    Int ts = 0;
    vector<Int> tss(n, ts);  // timestamp
    auto dfs = FIX([&](auto&& self, Int v, Int flmax) -> Int {
        if(v == t) return flmax;
        tss[v] = ts;

        Int res = 0;
        for(auto& e : g[v]) {
            if(tss[e.to] == ts) continue;
            Int flmax_nex = MIN(e.cap, flmax);
            if(flmax_nex == 0) continue;
            Int fl = self(e.to, flmax_nex);
            flmax -= fl;

            auto& e_rev = g[e.to][e.rev];
            e.cap     -= fl;
            e_rev.cap += fl;
            res += fl;
        }
        return res;
    });

    Int res = 0;
    for(;;) {
        ++ts;
        Int fl = dfs(s, INF);
        if(fl == 0) break;
        res += fl;
    }

    return res;
}

Int flow_dinic(vector<vector<FlowEdge>>& g, Int s, Int t) {
    Int n = SIZE(g);

    vector<Int> ds(n);
    auto bfs = [&]() {
        queue<Int> que;
        ALL(fill, ds, -1);
        que.emplace(s);
        ds[s] = 0;

        while(!que.empty()) {
            Int v = POP(que);
            for(const auto& e : g[v]) {
                if(ds[e.to] >= 0) continue;
                if(e.cap == 0) continue;
                que.emplace(e.to);
                ds[e.to] = ds[v] + 1;
            }
        }
    };

    vector<Int> idxs(n);
    auto dfs = FIX([&](auto&& self, Int v, Int flmax) -> Int {
        if(v == t) return flmax;

        for(Int& i = idxs[v]; i < SIZE(g[v]); ++i) {
            auto& e = g[v][i];
            if(ds[v] >= ds[e.to]) continue;
            if(e.cap == 0) continue;
            Int fl = self(e.to, MIN(e.cap, flmax));
            if(fl > 0) {
                auto& e_rev = g[e.to][e.rev];
                e.cap     -= fl;
                e_rev.cap += fl;
                return fl;
            }
        }
        return 0;
    });

    Int res = 0;
    for(;;) {
        bfs();
        if(ds[t] < 0) break;

        ALL(fill, idxs, 0);
        for(;;) {
            Int fl = dfs(s, INF);
            if(fl == 0) break;
            res += fl;
        }
    }

    return res;
}

// }}}
