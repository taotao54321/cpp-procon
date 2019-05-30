#include "procon.hpp"
#include "num.hpp"

signed main() {
    i64 N = RD();

    auto ts = factorize(N);
    vector<i64> ans;
    for(const auto& t : ts) {
        i64 p,e; tie(p,e) = t;
        fill_n(back_inserter(ans), e, p);
    }

    PRINT(N);
    PRINT(": ");
    PRINTLN(ans);

    EXIT();
}
