#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"
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
#include "../../../include/fold_queue.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int L = RD();

    auto que = fold_queue_make<Int>(LIFT(MIN), INF);
    auto ans = vec_reserve<Int>(N-L+1);
    LOOP(N) {
        Int a = RD();
        que.emplace(a);

        if(SIZE(que) == L) {
            ans.emplace_back(que.fold());
            que.pop();
        }
    }

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
