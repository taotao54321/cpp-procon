#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/3/CGL_3_C"
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
    Int N = RD();
    auto PS = RD_VEC<Vec>(N);

    Polygon poly(move(PS));

    Int Q = RD();
    LOOP(Q) {
        auto P = RD<Vec>();

        auto ans = poly.containment(P);
        if(ans == GEO_CONT_OUT)
            PRINTLN(0);
        else if(ans == GEO_CONT_ON)
            PRINTLN(1);
        else if(ans == GEO_CONT_IN)
            PRINTLN(2);
        else
            ASSERT(false);
    }
}

signed main() {
    solve();

    EXIT();
}
