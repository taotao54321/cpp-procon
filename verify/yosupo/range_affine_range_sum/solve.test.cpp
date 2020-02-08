#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
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
    Int N = RD();
    Int Q = RD();

    using Monoid = pair<Int,ModInt>;
    using Action = pair<ModInt,ModInt>;

    auto A = vec_reserve<Monoid>(N);
    LOOP(N) {
        Int a = RD();
        A.emplace_back(1, a);
    }

    auto seg = segtree_lazy_range<Monoid,Action>(
        [](const Monoid& ml, const Monoid& mr) -> Monoid { return {ml.first+mr.first, ml.second+mr.second}; },
        [](const Monoid& m, const Action& a) -> Monoid {
            auto [b,c] = a;
            return {m.first, b*m.second + c*m.first};
        },
        [](const auto& al, const auto& ar) -> Action {
            auto [b1,c1] = al;
            auto [b2,c2] = ar;
            return {b1*b2, b2*c1 + c2};
        },
        make_pair(1,0),
        make_pair(1,0),
        begin(A), end(A)
    );
    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int l = RD();
            Int r = RD();
            Action a = RD<Action>();
            seg.act(l, r, a);
        }
        else if(cmd == 1) {
            Int l = RD();
            Int r = RD();
            auto ans = seg.query(l,r).second;
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
