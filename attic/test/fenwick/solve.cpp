#include "procon.hpp"
#include "coord_compress.hpp"
#include "fenwick.hpp"

signed main() {
    i64 N = RD();
    auto A = RD_VEC(N);

    // A を座標圧縮して [0,N) にする
    vector<i64> xs(A);
    unordered_map<i64,i64> m;
    coord_compress(xs, m);
    for(i64& e : A)
        e = m[e];

    Fenwick<i64> fen(N);
    i64 ans = 0;
    REP(i, N) {
        i64 a = A[i];
        ans += i - fen.query(0,a);  // i から既に現れた [0,i) の個数を引く
        fen.add(a, 1);
    }

    PRINTLN(ans);

    EXIT();
}
