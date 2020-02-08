#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"
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
#include "../../../include/graph.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int M = RD();

    auto G = vec_make<Int>(N,N, INF);
    REP(i, N) { G[i][i] = 0; }
    LOOP(M) {
        Int a = RD();
        Int b = RD();
        Int c = RD();
        G[a][b] = c;
    }

    bool ok; tie(ok,ignore) = graph_floyd(G);
    if(!ok) {
        PRINTLN("NEGATIVE CYCLE");
        return;
    }

    REP(i, N) {
        REP(j, N) {
            if(j != 0) PRINT(' ');
            if(G[i][j] == INF)
                PRINT("INF");
            else
                PRINT(G[i][j]);
        }
        PRINTLN();
    }
}

signed main() {
    solve();

    EXIT();
}
