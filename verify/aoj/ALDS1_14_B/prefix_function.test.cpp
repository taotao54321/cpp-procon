#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/14/ALDS1_14_B"
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
#include "../../../include/prefix_function.hpp"

//--------------------------------------------------------------------

void solve() {
    auto T = RD<string>();
    auto P = RD<string>();

    auto S = P + '$' + T;
    auto pi = ALL(prefix_function, S);

    vector<i64> ans;
    REP(i, SIZE(T)-SIZE(P)+1) {
        if(pi[SIZE(P)+1+i+SIZE(P)-1] == SIZE(P))
            ans.emplace_back(i);
    }

    ALL(for_each, ans, LIFT(PRINTLN));
}

signed main() {
    solve();

    EXIT();
}
