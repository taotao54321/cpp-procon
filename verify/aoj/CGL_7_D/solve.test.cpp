#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_D"
#define ERROR "1e-6"

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
    auto C = RD<Vec>();
    auto R = RD<Real>();
    Circle cir(C, R);

    Int Q = RD();
    LOOP(Q) {
        auto P0 = RD<Vec>();
        auto P1 = RD<Vec>();
        Line l(P0, P1);

        auto ans = geo_crosspoints(cir, l);
        ALL(sort, ans);

        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
