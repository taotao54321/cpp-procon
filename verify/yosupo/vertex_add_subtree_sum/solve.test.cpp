#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
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
#include "../../../include/euler_tour.hpp"
#include "../../../include/segtree.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int Q = RD();
    auto A = RD_VEC(N);

    vector<vector<Int>> G(N);
    FOR(v, 1, N) {
        Int p = RD();
        G[v].emplace_back(p);
        G[p].emplace_back(v);
    }

    vector<Int> ls,rs; tie(ls,rs) = euler_tour_vertex(G, 0);

    vector<Int> data(N);
    REP(v, N) {
        data[ls[v]] = A[v];
    }
    auto seg = segtree_rq_range<Int,Int>(
        plus<>{},
        plus<>{},
        0,
        begin(data), end(data)
    );

    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int v = RD();
            Int a = RD();
            seg.act(ls[v], a);
        }
        else if(cmd == 1) {
            Int v = RD();
            Int ans = seg.query(ls[v], rs[v]);
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
