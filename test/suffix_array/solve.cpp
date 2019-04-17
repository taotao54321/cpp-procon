#include "procon.hpp"
#include "suffix_array.hpp"

signed main() {
    string S; RD(S);
    i64 M; RD(M);

    auto sa = ALL(make_suffix_array, S);

    i64 ans = 0;
    REP(_, M) {
        string t; RD(t);

        auto p = ALL(sa.equal_range, t);
        if(distance(FST(p),SND(p)) > 0)
            assert(*ALL(sa.find,t) == *FST(p));
        ans += distance(FST(p), SND(p));
    }

    PRINTLN(ans);

    EXIT();
}
