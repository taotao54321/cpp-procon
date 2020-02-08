#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B"
//#define ERROR "1e-6"

#define ASSERT_LV 2
// header {{{
#include "../../../include/stdc++.hpp"
using namespace std;

#include "../../../include/types.hpp"
// }}}

using Int  = i32;
using Real = f80;

constexpr Int MOD = 1'000'000'007;
//constexpr Int MOD = 998'244'353;

constexpr Real EPS = Real(1e-10L);

constexpr int  COUT_PREC      = 15;
constexpr bool COUT_AUTOFLUSH = false;

#include "../../../include/procon.hpp"
#include "../../../include/graph.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int M = RD();
    Int R = RD();

    vector<vector<pair<Int,Int>>> G(N);
    LOOP(M) {
        Int a = RD();
        Int b = RD();
        Int c = RD();
        G[a].emplace_back(b, c);
    }

    vector<Int> ds; tie(ds,ignore) = graph_bellman(G, R);
    if(ALL(find, ds, -INF) != end(ds)) {
        PRINTLN("NEGATIVE CYCLE");
        return;
    }

    REP(i, N) {
        if(ds[i] == INF)
            PRINTLN("INF");
        else
            PRINTLN(ds[i]);
    }
}

signed main() {
    solve();

    EXIT();
}
