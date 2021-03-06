#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_A"
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
#include "../../../include/geo.hpp"

//--------------------------------------------------------------------

void solve() {
    auto C0 = RD<Vec>();
    auto R0 = RD<Real>();
    auto C1 = RD<Vec>();
    auto R1 = RD<Real>();

    Circle cir0(C0, R0);
    Circle cir1(C1, R1);

    Int ans = geo_common_tangent_count(cir0, cir1);

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
