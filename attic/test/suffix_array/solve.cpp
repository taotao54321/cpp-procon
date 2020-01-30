#include "procon.hpp"
#include "suffix_array.hpp"

signed main() {
    auto S = RD<string>();
    i64 M = RD();

    auto sa = ALL(make_suffix_array, S);

    i64 ans = 0;
    REP(_, M) {
        auto t = RD<string>();

        auto p = ALL(sa.equal_range, t);
        if(distance(FST(p),SND(p)) > 0)
            ASSERT(*ALL(sa.find,t) == *FST(p));
        ans += distance(FST(p), SND(p));
    }

    PRINTLN(ans);

    EXIT();
}
