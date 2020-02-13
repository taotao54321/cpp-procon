#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D"
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
#include "../../../include/fenwick.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();

    auto G = vec_reserve<vector<pair<Int,Int>>>(N);
    REP(v, N) {
        Int k = RD();
        auto es = vec_reserve<pair<Int,Int>>(k);
        LOOP(k) {
            Int c = RD();
            es.emplace_back(c, 0);
        }
        G.emplace_back(move(es));
    }

    vector<Int> ds,us; tie(ds,us,ignore) = euler_tour_edge(G, 0);

    Fenwick<Int> fen(2*N);

    Int Q = RD();
    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int v = RD();
            Int x = RD();

            fen.add(ds[v],  x);
            fen.add(us[v], -x);
        }
        else if(cmd == 1) {
            Int v = RD();

            Int ans = fen.query0(ds[v]+1);
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
