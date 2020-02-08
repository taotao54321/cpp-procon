#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_D"
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
    Int Q = RD();
    LOOP(Q) {
        auto PS = RD_VEC<Vec>(4);
        Segment s1(PS[0], PS[1]);
        Segment s2(PS[2], PS[3]);

        auto ans = geo_distance(s1, s2);
        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
