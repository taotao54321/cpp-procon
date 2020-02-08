#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2579"
#define ERROR "1e-7"

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
#include "../../../include/geo.hpp"

//--------------------------------------------------------------------

void solve() {
    constexpr Real XMIN =  0;
    constexpr Real XMAX = 50;
    constexpr Real YMIN =  0;
    constexpr Real YMAX = 94;

    constexpr Vec START { 25,  0 };
    constexpr Vec GOAL  { 25, 94 };

    Int N = RD();
    Int D = RD();
    vector<Circle> C;
    LOOP(N) {
        auto P = RD<Vec>();
        auto R = RD<Real>();
        C.emplace_back(P, R);
    }

    vector<Line> ls_fwd;
    for(const auto& cir : C) {
        auto ps = geo_tangent(cir, START);
        ls_fwd.emplace_back(START, ps[0]);
        ls_fwd.emplace_back(START, ps[1]);
    }

    vector<Line> ls_bak;
    for(const auto& cir : C) {
        auto ps = geo_tangent(cir, GOAL);
        ls_bak.emplace_back(GOAL, ps[0]);
        ls_bak.emplace_back(GOAL, ps[1]);
    }

    Real ans = FINF;
    {
        Segment s(START, GOAL);
        Int cnt = 0;
        for(const auto& cir : C) {
            if(geo_intersects(cir,s)) {
                if(EQ_EPS(geo_distance(cir.c,s), cir.r)) continue;
                ++cnt;
            }
        }
        if(cnt <= D)
            chmin(ans, s.abs());
    }

    for(const auto& l0 : ls_fwd) for(const auto& l1 : ls_bak) {
        if(!geo_intersects(l0, l1)) continue;
        auto p = geo_crosspoint(l0, l1);
        if(LT_EPS(p.x,XMIN) || LT_EPS(XMAX,p.x)) continue;
        if(LT_EPS(p.y,YMIN) || LT_EPS(YMAX,p.y)) continue;

        Int cnt = 0;

        Segment s0(START, p);
        for(const auto& cir : C) {
            if(geo_intersects(cir,s0)) {
                if(EQ_EPS(geo_distance(cir.c,s0), cir.r)) continue;
                if(cir.containment(p) == GEO_CONT_IN) continue;
                ++cnt;
            }
        }
        Segment s1(GOAL, p);
        for(const auto& cir : C) {
            if(geo_intersects(cir,s1)) {
                if(EQ_EPS(geo_distance(cir.c,s1), cir.r)) continue;
                ++cnt;
            }
        }

        if(cnt <= D)
            chmin(ans, s0.abs() + s1.abs());
    }
    if(EQ_EXACT(ans, FINF)) {
        PRINTLN(-1);
        return;
    }

    PRINTLN(ans);
}

signed main() {
    solve();

    EXIT();
}
