#include "procon.hpp"
#include "fold_queue.hpp"

[[noreturn]] void impossible() {
    PRINTLN(-1);
    EXIT();
}

signed main() {
    i64 N = RD();
    i64 K = RD();
    auto S = RD<string>();

    vector<pair<i64,i64>> v(N+1, make_pair(INF,INF));  // (最短手数,実現する最小歩数)
    v[N] = {0,0};

    auto que = make_fold_queue<pair<i64,i64>>(GENERIC(min));  // (最短手数,インデックス)
    que.emplace(0, N);

    for(i64 i = N-1; i >= 0; --i) {
        i64 x,j; tie(x,j) = que.fold();

        if(S[i] == '0' && x != INF)
            v[i] = {x+1, j-i};
        else
            v[i] = {INF, INF};

        if(SIZE(que) == K)
            que.pop();
        que.emplace(v[i].first, i);
    }

    if(v[0].first == INF) impossible();

    vector<i64> ans;
    ans.reserve(v[0].first);
    for(i64 i = 0; i != N; i += v[i].second)
        ans.emplace_back(v[i].second);

    PRINTLN(ans);

    EXIT();
}
