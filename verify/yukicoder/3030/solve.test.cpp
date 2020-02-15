#define PROBLEM "https://yukicoder.me/problems/no/3030"
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
    LOOP(N) {
        Int x = RD();
        bool ans = is_prime(x);
        PRINTLN(x, ans?1:0);
    }
}

signed main() {
    solve();

    EXIT();
}
