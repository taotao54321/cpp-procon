#include "procon.hpp"
#include "graph.hpp"
#include "serial.hpp"

i64 vertex(i64 station, i64 company) {
    static Serial serial(0);
    static HashMap<pair<i64,i64>,i64> m;

    auto key = make_pair(station, company);
    auto it = m.find(key);
    if(it == end(m))
        it = m.insert(it, make_pair(key,serial.next()));

    return it->second;
}

signed main() {
    i64 N = RD();
    i64 M = RD();

    vector<vector<pair<i64,i64>>> G(N+2*M);
    vector<vector<i64>> companies(N);
    REP(_, M) {
        i64 p = RD1();
        i64 q = RD1();
        i64 c = RD1();
        G[vertex(p,c)].emplace_back(vertex(q,c), 0);
        G[vertex(q,c)].emplace_back(vertex(p,c), 0);
        companies[p].emplace_back(c);
        companies[q].emplace_back(c);
    }

    REP(i, N) {
        for(const auto& c : companies[i]) {
            G[vertex(i,c)].emplace_back(vertex(i,-1), 0);  // 改札を出るのはタダ
            G[vertex(i,-1)].emplace_back(vertex(i,c), 1);  // 改札を通るとき課金
        }
    }

    vector<i64> d;
    tie(d,ignore) = graph_k_bfs(G, 1, vertex(0,-1));

    i64 ans = d[vertex(N-1,-1)];

    PRINTLN(ans == INF ? -1 : ans);

    EXIT();
}
