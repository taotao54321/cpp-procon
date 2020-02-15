#define PROBLEM "https://yukicoder.me/problems/no/117"
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
#include "../../../include/num.hpp"

//--------------------------------------------------------------------

template<class T>
void RD_EXPECT(const T& expect) {
    auto actual = RD<T>();
    ASSERT(actual == expect);
}

void solve() {
    using Fac = Factorial<2'000'000>;

    Int T = RD();
    LOOP(T) {
        char F = RD<char>();
        RD_EXPECT<char>('(');
        Int N = RD();
        RD_EXPECT<char>(',');
        Int K = RD();
        RD_EXPECT<char>(')');

        ModInt ans;
        if(F == 'P')
            ans = Fac::perm(N, K);
        else if(F == 'C')
            ans = Fac::comb(N, K);
        else if(F == 'H')
            ans = Fac::comb_rep(N, K);
        else
            ASSERT(false);

        PRINTLN(ans);
    }
}

signed main() {
    solve();

    EXIT();
}
