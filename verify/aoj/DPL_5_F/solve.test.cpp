#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_F"
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
#include "../../../include/num.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int K = RD();

    using Fac = Factorial<1000>;

    auto ans = Fac::comb(N-1, K-1);
    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
