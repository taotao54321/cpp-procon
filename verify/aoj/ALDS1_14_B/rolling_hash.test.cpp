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
#include "../../../include/rolling_hash.hpp"

//--------------------------------------------------------------------

void solve() {
    auto T = RD<string>();
    auto P = RD<string>();

    if(SIZE(T) < SIZE(P)) return;

    i64 h = ALL(rolling_hash_make,P).get(0,SIZE(P));
    auto rh_t = ALL(rolling_hash_make, T);
    vector<Int> ans;
    REP(i, SIZE(T)) {
        if(rh_t.get(i,i+SIZE(P)) == h)
            ans.emplace_back(i);
    }

    ALL(for_each, ans, LIFT(PRINTLN));
}

signed main() {
    solve();

    EXIT();
}
