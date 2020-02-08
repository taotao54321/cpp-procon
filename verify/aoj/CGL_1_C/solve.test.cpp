#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C"
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
    const map<GeoCcw,string> CCW_STR {
        { GEO_CCW_CCW,   "COUNTER_CLOCKWISE" },
        { GEO_CCW_CW,    "CLOCKWISE"         },
        { GEO_CCW_BACK,  "ONLINE_BACK"       },
        { GEO_CCW_FRONT, "ONLINE_FRONT"      },
        { GEO_CCW_ON,    "ON_SEGMENT"        },
    };

    auto P0 = RD<Vec>();
    auto P1 = RD<Vec>();
    Int Q = RD();

    LOOP(Q) {
        auto P2 = RD<Vec>();

        auto ccw = geo_ccw(P0, P1, P2);
        auto ans = CCW_STR.at(ccw);
        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
