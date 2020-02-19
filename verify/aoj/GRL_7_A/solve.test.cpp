#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A"
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
#include "../../../include/bimatch.hpp"

//--------------------------------------------------------------------

void solve() {
    Int X = RD();
    Int Y = RD();
    Int N = X+Y;
    Int M = RD();

    vector<vector<Int>> G(N);
    LOOP(M) {
        Int a = RD();
        Int b = RD(); b += X;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    Int ans; tie(ans,ignore) = bimatch(G);

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
