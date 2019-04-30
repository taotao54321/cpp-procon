#include "procon.hpp"
#include "coord_compress.hpp"
#include "fenwick.hpp"

signed main() {
    i64 N; RD(N);
    auto A = RD_ARRAY<i64>(N);

    // A を座標圧縮して [0,N) にする
    vector<i64> xs(A);
    unordered_map<i64,i64> m;
    coord_compress(xs, m);
    ALL(transform_self, A, [&m](i64 e) { return m[e]; });

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
