#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2423"
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

bool is_ok(vector<Real> persons, vector<Real> holes) {
    Int m = SIZE(persons);
    Int n = SIZE(holes);

    ALL(sort, persons);
    ALL(sort, holes);

    Int j = 0;
    REP(i, m) {
        while(j < n && GT_EPS(persons[i], holes[j]))
            ++j;
        if(j >= n) return false;
        ++j;
    }

    return true;
}

void solve() {
    Int N = RD();
    Int M = RD();
    auto HOLES = RD_VEC<Real>(N);

    vector<vector<Vec>> FIGURES;
    LOOP(M) {
        Int K = RD();
        auto PS = RD_VEC<Vec>(K);
        FIGURES.emplace_back(PS);
    }

    vector<Real> PERSONS(M);
    REP(i, M) {
        PERSONS[i] = geo_min_ball(move(FIGURES[i])).r;
    }

    vector<Int> ans(M);
    vector<bool> used(N, false);
    REP(i, M) {
        Int j_ok = -1;
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

    for(Int& j : ans) ++j;  // 1-based

    ALL(for_each, ans, LIFT(PRINTLN));
}

signed main() {
    solve();

    EXIT();
}
