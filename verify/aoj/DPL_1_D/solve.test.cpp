#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D"
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
#include "../../../include/lis.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    auto A = RD_VEC(N);

    auto dp = ALL(lis_strict_dp, A);
    Int ans = *ALL(max_element, dp);

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
