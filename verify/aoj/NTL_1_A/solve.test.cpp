#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A"
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
#include "../../../include/num.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();

    auto fs = factorize(N);

    PRINT(N);
    PRINT(':');
    for(const auto& f : fs) {
        Int p,e; tie(p,e) = f;
        LOOP(e) {
            PRINT(' ');
            PRINT(p);
        }
    }
}

signed main() {
    solve();

    EXIT();
}
