#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
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
    auto A = RD_VEC(N);

    auto seg = segtree_rq_range<Int,Int>(
        plus<>{},
        plus<>{},
        0,
        begin(A), end(A)
    );
    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int i = RD();
            Int a = RD();
            seg.act(i, a);
        }
        else if(cmd == 1) {
            Int l = RD();
            Int r = RD();
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
