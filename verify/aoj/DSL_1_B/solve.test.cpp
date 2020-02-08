#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B"
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
#include "../../../include/union_find.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int Q = RD();

    WeightedUnionFind<Int> wuf(N);
    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int x = RD();
            Int y = RD();
            Int z = RD();
            bool ok = wuf.unite(x, y, z);
            ASSERT(ok);
        }
        else if(cmd == 1) {
            Int x = RD();
            Int y = RD();
            if(wuf.is_same(x,y)) {
                Int ans = wuf.weight(y) - wuf.weight(x);
                PRINTLN(ans);
            }
            else {
                PRINTLN('?');
            }
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
