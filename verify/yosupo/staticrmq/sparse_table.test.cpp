#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
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
#include "../../../include/sparse_table.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int Q = RD();
    auto A = RD_VEC(N);

    auto st = sparse_table_range<Int>(LIFT(MIN), begin(A), end(A));
    LOOP(Q) {
        Int l = RD();
        Int r = RD();
        Int ans = st.query(l, r);
        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
