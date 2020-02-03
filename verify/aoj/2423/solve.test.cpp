#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2423"
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
#include "../../../include/geo.hpp"

//--------------------------------------------------------------------

bool is_ok(vector<Real> persons, vector<Real> holes) {
    i64 m = SIZE(persons);
    i64 n = SIZE(holes);

    ALL(sort, persons);
    ALL(sort, holes);

    i64 j = 0;
    REP(i, m) {
        while(j < n && GT_EPS(persons[i], holes[j]))
            ++j;
        if(j >= n) return false;
        ++j;
    }

    return true;
}

void solve() {
    i64 N = RD();
    i64 M = RD();
    auto HOLES = RD_VEC<Real>(N);

    vector<vector<Vec>> FIGURES;
    LOOP(M) {
        i64 K = RD();
        auto PS = RD_VEC<Vec>(K);
        FIGURES.emplace_back(PS);
    }

    vector<Real> PERSONS(M);
    REP(i, M) {
        PERSONS[i] = geo_min_ball(move(FIGURES[i])).r;
    }

    vector<i64> ans(M);
    vector<bool> used(N, false);
    REP(i, M) {
        i64 j_ok = -1;
        REP(j, N) {
            if(used[j]) continue;
            if(GT_EPS(PERSONS[i], HOLES[j])) continue;
            used[j] = true;

            vector<Real> persons(begin(PERSONS)+i+1, end(PERSONS));
            vector<Real> holes;
            REP(k, N) {
                if(used[k]) continue;
                holes.emplace_back(HOLES[k]);
            }

            if(is_ok(move(persons), move(holes))) {
                j_ok = j;
                break;
            }
            used[j] = false;
        }

        if(j_ok == -1) {
            PRINTLN("NG");
            return;
        }
        ans[i] = j_ok;
    }

    for(i64& j : ans) ++j;  // 1-based

    ALL(for_each, ans, LIFT(PRINTLN));
}

signed main() {
    solve();

    EXIT();
}
