#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0323"
#define ERROR "1e-3"

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
#include "../../../include/trisect.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
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
