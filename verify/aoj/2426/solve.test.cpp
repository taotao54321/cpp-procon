#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426"
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
#include "../../../include/coord_compress.hpp"
#include "../../../include/cum2.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int M = RD();
    auto A = RD_VEC<pair<Int,Int>>(N);

    CoordCompress ccy(N);
    CoordCompress ccx(N);
    for(auto [x,y] : A) {
        ccy.insert(y);
        ccx.insert(x);
    }
    ccy.build();
    ccx.build();
    Int h = SIZE(ccy);
    Int w = SIZE(ccx);

    auto cum = cum2_default<Int>(h,w);
    for(auto [x,y] : A) {
        y = ccy.comp(y);
        x = ccx.comp(x);
        ++cum.at(y,x);
    }
    cum.build();

    LOOP(M) {
        Int x1 = RD();
        Int y1 = RD();
        Int x2 = RD();
        Int y2 = RD();

        y1 = ccy.lower_bound(y1);
        x1 = ccx.lower_bound(x1);
        y2 = ccy.upper_bound(y2);
        x2 = ccx.upper_bound(x2);
        Int ans = cum.query(y1, x1, y2, x2);
        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
