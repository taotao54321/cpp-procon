#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
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
    Int Q = RD();

    HashMap<Int,Int> m;
    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int k = RD();
            Int v = RD();
            m[k] = v;
        }
        else if(cmd == 1) {
            Int k = RD();
            Int ans = m[k];
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
