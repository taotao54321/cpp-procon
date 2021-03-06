#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"
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

    auto G = vec_reserve<vector<Int>>(N);
    LOOP(N) {
        Int K = RD();
        auto vs = RD_VEC(K);
        G.emplace_back(vs);
    }

    auto lca = Lca(G, 0);
    Int Q = RD();
    LOOP(Q) {
        Int a = RD();
        Int b = RD();
        Int ans = lca.query(a, b);
        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
