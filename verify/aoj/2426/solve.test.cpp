#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426"
//#define ERROR "1e-6"

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
#include "../../../include/cum2.hpp"

//--------------------------------------------------------------------

void solve() {
    i64 N = RD();
    i64 M = RD();
    auto A = RD_VEC<pair<i64,i64>>(N);

    CoordCompress ccy(N);
    CoordCompress ccx(N);
    for(auto [x,y] : A) {
        ccy.insert(y);
        ccx.insert(x);
    }
    ccy.build();
    ccx.build();
    i64 h = SIZE(ccy);
    i64 w = SIZE(ccx);

    auto cum = cum2_default<i64>(h,w);
    for(auto [x,y] : A) {
        y = ccy.comp(y);
        x = ccx.comp(x);
        ++cum.at(y,x);
    }
    cum.build();

    LOOP(M) {
        i64 x1 = RD();
        i64 y1 = RD();
        i64 x2 = RD();
        i64 y2 = RD();

        y1 = ccy.lower_bound(y1);
        x1 = ccx.lower_bound(x1);
        y2 = ccy.upper_bound(y2);
        x2 = ccx.upper_bound(x2);
        i64 ans = cum.query(y1, x1, y2, x2);
        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
