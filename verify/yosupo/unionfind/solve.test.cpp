#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
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

    UnionFind uf(N);
    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int x = RD();
            Int y = RD();
            uf.unite(x, y);
        }
        else if(cmd == 1) {
            Int x = RD();
            Int y = RD();
            bool ans = uf.is_same(x, y);
            PRINTLN(ans ? 1 : 0);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
