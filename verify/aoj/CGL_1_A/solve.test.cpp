#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_A"
#define ERROR "1e-8"

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
#include "../../../include/geo.hpp"

//--------------------------------------------------------------------

void solve() {
    auto P1 = RD<Vec>();
    auto P2 = RD<Vec>();
    Int Q = RD();

    Line l(P1, P2);
    LOOP(Q) {
        auto P = RD<Vec>();
        auto ans = geo_project(l, P);
        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
