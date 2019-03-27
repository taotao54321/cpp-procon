#include "procon.hpp"
#include "container.hpp"
#include "cum.hpp"
#include "coord_compress.hpp"

signed main() {
    i64 N; RD(N);
    i64 M; RD(M);

    vector<pair<i64,i64>> yxs;
    yxs.reserve(N);
    REP(_, N) {
        i64 x,y; RD(x); RD(y);
        yxs.emplace_back(y,x);
    }

    vector<i64> ys; ys.reserve(N);
    vector<i64> xs; xs.reserve(N);
    for(const auto& yx : yxs) {
        i64 y,x; tie(y,x) = yx;
        ys.emplace_back(y);
        xs.emplace_back(x);
    }
    ys.insert(end(ys), { -INF, INF });
    xs.insert(end(xs), { -INF, INF });
    map<i64,i64> ycomp, xcomp;
    coord_compress(ys, ycomp);
    coord_compress(xs, xcomp);
    ALL(transform_self, yxs, [&ycomp,&xcomp](const auto& yx) {
        i64 y,x; tie(y,x) = yx;
        return make_pair(ycomp[y], xcomp[x]);
    });

    i64 h = SIZE(ycomp);
    i64 w = SIZE(xcomp);
    Cum2<i64> cum(h, w);
    for(const auto& yx : yxs) {
        i64 y,x; tie(y,x) = yx;
        cum.add(y, x, 1);
    }
    cum.build();

    REP(_, M) {
        i64 x1,y1; RD(x1); RD(y1);
        i64 x2,y2; RD(x2); RD(y2);
        i64 yy1 = map_search_ge(ycomp,y1)->second;
        i64 xx1 = map_search_ge(xcomp,x1)->second;
        i64 yy2 = map_search_le(ycomp,y2)->second;
        i64 xx2 = map_search_le(xcomp,x2)->second;
        i64 hh = yy2 - yy1 + 1;
        i64 ww = xx2 - xx1 + 1;

        i64 ans = cum.query(yy1, xx1, hh, ww);
        PRINTLN(ans);
    }

    EXIT();
}
