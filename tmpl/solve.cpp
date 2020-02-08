/**
 * 
 */

#define ASSERT_LV 1
// header {{{
#include "../include/stdc++.hpp"
using namespace std;

#include "../include/types.hpp"
// }}}

using Int  = i64;
using Real = f80;

constexpr Int MOD = 1'000'000'007;
//constexpr Int MOD = 998'244'353;

constexpr Real EPS = Real(1e-10L);

constexpr int  COUT_PREC      = 15;
constexpr bool COUT_AUTOFLUSH = false;

#include "../include/procon.hpp"

//--------------------------------------------------------------------

[[noreturn]] void impossible() {
    PRINTLN("-1");
    EXIT();
}



void solve() {
    

    //PRINTLN(ans);
}

signed main() {
    Int T = 1; //RD();
    LOOP(T) {
        solve();
    }

    EXIT();
}
