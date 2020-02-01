#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/5/DSL_5_B"
//#define ERROR "1e-6"

#define ASSERT_LV 2
// header {{{
#include "../../../include/stdc++.hpp"
using namespace std;

using i8  = int8_t;
using u8  = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
#ifdef __SIZEOF_INT128__
using i128 = __int128;
using u128 = unsigned __int128;
#endif

using f32 = float;
using f64 = double;
using f80 = long double;

template<class T> constexpr T PROCON_INF();
// }}}

using Real = f80;

template<> constexpr i64  PROCON_INF<i64>()  { return INT64_C(1'010'000'000'000'000'017); }
template<> constexpr Real PROCON_INF<Real>() { return Real(1e100L); }

constexpr i64 MOD = INT64_C(1'000'000'007);
//constexpr i64 MOD = INT64_C(998'244'353);

constexpr Real EPS = Real(1e-10L);

constexpr int  COUT_PREC      = 15;
constexpr bool COUT_AUTOFLUSH = false;

#include "../../../include/procon.hpp"
#include "../../../include/coord_compress.hpp"
#include "../../../include/imos2.hpp"

//--------------------------------------------------------------------

void solve() {
    i64 N = RD();
    auto A = RD_VEC<tuple<i64,i64,i64,i64>>(N);

    CoordCompress ccy(1001);
    CoordCompress ccx(1001);
    for(const auto& a : A) {
        i64 x1,y1,x2,y2; tie(x1,y1,x2,y2) = a;
        ccy.insert({y1,y2});
        ccx.insert({x1,x2});
    }
    ccy.build();
    ccx.build();
    i64 h = SIZE(ccy);
    i64 w = SIZE(ccx);

    auto imos = imos2_default<i64>(h,w);
    for(const auto& a : A) {
        i64 x1,y1,x2,y2; tie(x1,y1,x2,y2) = a;
        y1 = ccy.comp(y1);
        x1 = ccx.comp(x1);
        y2 = ccy.comp(y2);
        x2 = ccx.comp(x2);
        imos.add(y1, x1, y2, x2, 1);
    }
    imos.build();

    i64 ans = 0;
    REP(y, h) REP(x, w) {
        chmax(ans, imos.at(y,x));
    }

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
