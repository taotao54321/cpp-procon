#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"
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
#include "../../../include/flow.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int M = RD();

    vector<vector<FlowEdge>> G(N);
    LOOP(M) {
        Int a = RD();
        Int b = RD();
        Int c = RD();
        flow_add_edge(G, a, b, c);
    }

    Int ans = flow_ford_fulkerson(G, 0, N-1);

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
