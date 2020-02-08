#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/14/ALDS1_14_B"
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
#include "../../../include/z_function.hpp"

//--------------------------------------------------------------------

void solve() {
    auto T = RD<string>();
    auto P = RD<string>();

    auto S = P + '$' + T;
    auto z = ALL(z_function, S);

    vector<Int> ans;
    REP(i, SIZE(T)-SIZE(P)+1) {
        if(z[SIZE(P)+1+i] == SIZE(P))
            ans.emplace_back(i);
    }

    ALL(for_each, ans, LIFT(PRINTLN));
}

signed main() {
    solve();

    EXIT();
}
