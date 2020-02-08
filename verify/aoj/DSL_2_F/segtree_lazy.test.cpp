#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F"
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
#include "../../../include/segtree.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int Q = RD();

    auto seg = segtree_lazy_make<Int,Int>(
        LIFT(MIN),
        [](Int, Int a) { return a; },
        [](Int, Int a) { return a; },
        INF,
        INF,
        N,
        BIT_I_1(31)
    );
    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int l = RD();
            Int r = RD(); ++r;
            Int x = RD();
            seg.act(l, r, x);
        }
        else if(cmd == 1) {
            Int l = RD();
            Int r = RD(); ++r;
            Int ans = seg.query(l, r);
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
