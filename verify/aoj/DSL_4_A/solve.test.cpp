#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/4/DSL_4_A"
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
#include "../../../include/imos2.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    auto A = RD_VEC<tuple<Int,Int,Int,Int>>(N);

    CoordCompress ccy(2*N);
    CoordCompress ccx(2*N);
    for(const auto& a : A) {
        Int x1,y1,x2,y2; tie(x1,y1,x2,y2) = a;
        ccy.insert({y1,y2});
        ccx.insert({x1,x2});
    }
    ccy.build();
    ccx.build();
    Int h = SIZE(ccy);
    Int w = SIZE(ccx);

    auto imos = imos2_default<Int>(h,w);
    for(const auto& a : A) {
        Int x1,y1,x2,y2; tie(x1,y1,x2,y2) = a;
        y1 = ccy.comp(y1);
        x1 = ccx.comp(x1);
        y2 = ccy.comp(y2);
        x2 = ccx.comp(x2);
        imos.add(y1, x1, y2, x2, 1);
    }
    imos.build();

    Int ans = 0;
    REP(y, h-1) REP(x, w-1) {
        if(imos.at(y,x) == 0) continue;
        Int ch = ccy.uncomp(y+1) - ccy.uncomp(y);
        Int cw = ccx.uncomp(x+1) - ccx.uncomp(x);
        ans += ch * cw;
    }

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
