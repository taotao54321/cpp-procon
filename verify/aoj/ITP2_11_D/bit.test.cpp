#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/11/ITP2_11_D"
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

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int K = RD();

    Int mask = BIT_I_1(K);
    do {
        PRINT(mask);
        PRINT(':');
        REP(i, 18) {
            if(BIT_TEST(mask,i)) {
                PRINT(' ');
                PRINT(i);
            }
        }
        PRINTLN();
    } while(BIT_NEXT_SET_SIZED(mask, N));
}

signed main() {
    solve();

    EXIT();
}
