#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
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

constexpr int  COUT_PREC      = 0;
constexpr bool COUT_AUTOFLUSH = false;

#include "../../../include/procon.hpp"
#include "../../../include/geo.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    auto PS = RD_VEC<Vec>(N);

    ALL(sort, PS, Vec::lt_arg);
    auto it = ALL(upper_bound, PS, Vec{-1,0}, Vec::lt_arg);

    for_each(it, end(PS), LIFT(PRINTLN));
    for_each(begin(PS), it, LIFT(PRINTLN));
}

signed main() {
    solve();

    EXIT();
}
