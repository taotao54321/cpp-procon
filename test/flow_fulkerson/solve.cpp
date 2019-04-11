#include "procon.hpp"
#include "flow.hpp"

signed main() {
    i64 N; RD(N);
    i64 M; RD(M);

    auto G = arrayn_make<i64>(N,N, 0);
    REP(_, M) {
        i64 from,to; RD(from); RD(to);
        RD(G[from][to]);
    }
    //DBG(G);

    i64 f;
    vector<vector<i64>> flow;
    tie(f,flow) = flow_fulkerson(G, 0, N-1);
    //DBG(flow);

    // 始点から出る量が f であるか
    // 終点に入る量が f であるか
    i64 s_out = 0;
    i64 t_in  = 0;
    REP(w, N) {
        s_out += flow[0][w];
        t_in  += flow[w][N-1];
    }
    assert(f == s_out && s_out == t_in);

    // 始点/終点以外で入る量と出る量が等しいか
    FOR(v, 1, N-1) {
        i64 f_in  = 0;
        i64 f_out = 0;
        REP(w, N) {
            f_in  += flow[w][v];
            f_out += flow[v][w];
        }
        assert(f_in == f_out);
    }

    PRINTLN(f);

    EXIT();
}
