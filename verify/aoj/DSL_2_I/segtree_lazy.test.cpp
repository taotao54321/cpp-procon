#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I"
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
#include "../../../include/segtree.hpp"

//--------------------------------------------------------------------

void solve() {
    i64 N = RD();
    i64 Q = RD();

    auto seg = segtree_lazy_make<pair<i64,i64>,i64>(
        [](const auto& ml, const auto& mr) { return make_pair(ml.first+mr.first, ml.second+mr.second); },
        [](const auto& m, i64 a) { return make_pair(m.first, a*m.first); },
        [](i64, i64 a) { return a; },
        make_pair(1,0),
        INF,
        N,
        make_pair(1,0)
    );
    LOOP(Q) {
        i64 cmd = RD();
        if(cmd == 0) {
            i64 l = RD();
            i64 r = RD(); ++r;
            i64 x = RD();
            seg.act(l, r, x);
        }
        else if(cmd == 1) {
            i64 l = RD();
            i64 r = RD(); ++r;
            i64 ans = seg.query(l, r).second;
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
