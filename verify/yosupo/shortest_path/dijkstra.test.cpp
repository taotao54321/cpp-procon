#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
//#define ERROR "1e-6"

#define ASSERT_LV 2
// header {{{
#include "../../../include/stdc++.hpp"
using namespace std;

#include "../../../include/types.hpp"
// }}}

using Int  = i64;
using Real = f80;

constexpr Int MOD = 1'000'000'007;
//constexpr Int MOD = 998'244'353;

constexpr Real EPS = Real(1e-10L);

constexpr int  COUT_PREC      = 15;
constexpr bool COUT_AUTOFLUSH = false;

#include "../../../include/procon.hpp"
#include "../../../include/graph.hpp"

//--------------------------------------------------------------------

[[noreturn]] void impossible() {
    PRINTLN(-1);
    EXIT();
}

void solve() {
    Int N = RD();
    Int M = RD();
    Int S = RD();
    Int T = RD();

    vector<vector<pair<Int,Int>>> G(N);
    LOOP(M) {
        Int a = RD();
        Int b = RD();
        Int c = RD();
        G[a].emplace_back(b, c);
    }

    auto [ds,ps] = graph_dijkstra(G, S);
    if(ps[T] == -1) impossible();

    auto trace = vec_reserve<Int>(N);
    for(Int v = T; v != -1; v = ps[v])
        trace.emplace_back(v);
    ALL(reverse, trace);

    PRINTLN(ds[T], SIZE(trace)-1);
    REP(i, SIZE(trace)-1) {
        PRINTLN(trace[i], trace[i+1]);
    }
}

signed main() {
    solve();

    EXIT();
}
