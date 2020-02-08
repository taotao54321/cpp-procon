#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
//#define ERROR "1e-6"

#define ASSERT_LV 2
// header {{{
#include "../../../include/stdc++.hpp"
using namespace std;

#include "../../../include/types.hpp"
// }}}

using Int  = i64;
using Real = f80;

//constexpr Int MOD = 1'000'000'007;
constexpr Int MOD = 998'244'353;

constexpr Real EPS = Real(1e-10L);

constexpr int  COUT_PREC      = 15;
constexpr bool COUT_AUTOFLUSH = false;

#include "../../../include/procon.hpp"
#include "../../../include/segtree.hpp"

//--------------------------------------------------------------------

void solve() {
    using Monoid = pair<ModInt,ModInt>;

    Int N = RD();
    Int Q = RD();
    auto A = RD_VEC<Monoid>(N);

    auto seg = segtree_rq_range<Monoid,Monoid>(
        [](const auto& ml, const auto& mr) -> Monoid {
            auto [a1,b1] = ml;
            auto [a2,b2] = mr;
            return { a1*a2, a2*b1+b2 };
        },
        [](const auto&, const auto& a) { return a; },
        make_pair(1,0),
        begin(A), end(A)
    );
    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int i = RD();
            auto a = RD<Monoid>();
            seg.act(i, a);
        }
        else if(cmd == 1) {
            Int l = RD();
            Int r = RD();
            Int x = RD();
            auto m = seg.query(l, r);
            auto ans = m.first*x + m.second;
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
