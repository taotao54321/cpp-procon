#define PROBLEM "https://judge.yosupo.jp/problem/lca"
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
#include "../../../include/lca.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int Q = RD();

    vector<vector<Int>> G(N);
    FOR(v, 1, N) {
        Int p = RD();
        G[v].emplace_back(p);
        G[p].emplace_back(v);
    }

    auto lca = Lca(G, 0);
    LOOP(Q) {
        Int v = RD();
        Int w = RD();
        Int ans = lca.query(v, w);
        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
