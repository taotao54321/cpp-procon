// bfs_tour {{{

auto bfs_tour(const vector<vector<Int>>& g, Int root) {
    Int n = SIZE(g);
    vector<Int> idxs(n, -1);
    vector<Int> ps(n, -1);

    Int i = 0;
    queue<Int> que;
    que.emplace(root);
    while(!que.empty()) {
        Int v = POP(que);
        idxs[v] = i++;

        for(Int to : g[v]) {
            if(idxs[to] >= 0) continue;
            ps[to] = v;
            que.emplace(to);
        }
    }

    return make_pair(idxs, ps);
}

// }}}
