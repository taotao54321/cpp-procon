#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0323"
#define ERROR "1e-3"

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
#include "../../../include/trisect.hpp"

//--------------------------------------------------------------------

void solve() {
    i64 N = RD();
    auto A = RD_VEC<pair<Real,Real>>(N);

    Real xl = -FINF;
    Real xr =  FINF;
    for(auto [x,r] : A) {
        chmax(xl, x-r);
        chmin(xr, x+r);
    }

    auto f = [&A](Real x0) -> Real {
        Real res = FINF;
        for(auto [x,r] : A) {
            Real dx = x0 - x;
            chmin(res, r*r - dx*dx);
        }
        return res;
    };

    Real ans_x = trisect_max_real(xl, xr, f);
    Real ans = sqrt(f(ans_x));

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
