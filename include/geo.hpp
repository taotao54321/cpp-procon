// geo {{{

struct Vec {
    Real x{}, y{};

    constexpr Vec() = default;
    constexpr Vec(Real xx, Real yy) : x(xx), y(yy) {}

    static /*constexpr*/ Vec polar(Real r, Real theta) {
        return { r*cos(theta), r*sin(theta) };
    }

    constexpr Vec operator-() const { return {-x,-y}; }

    constexpr Vec& operator+=(const Vec& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    constexpr Vec& operator-=(const Vec& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    constexpr Vec& operator*=(Real rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    constexpr Vec& operator/=(Real rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    constexpr Real norm() const { return x*x + y*y; }
    /*constexpr*/ Real abs() const { return sqrt(norm()); }
    /*constexpr*/ Vec unit() const { return *this / abs(); }

    /*constexpr*/ Real arg() const { return atan2(y,x); }

    constexpr Real dot(const Vec& rhs) const {
        return x*rhs.x + y*rhs.y;
    }

    constexpr Real cross(const Vec& rhs) const {
        return x*rhs.y - y*rhs.x;
    }

    constexpr Vec rotate90() const {
        return {-y,x};
    }

    /*constexpr*/ Vec rotate(Real theta) const {
        return {
            x*cos(theta) - y*sin(theta),
            x*sin(theta) + y*cos(theta)
        };
    }

    static constexpr bool lt_arg(const Vec& lhs, const Vec& rhs) {
        // 零ベクトルは偏角最小とみなす
        if(lhs == rhs) return false;
        if(lhs == Vec{0,0}) return true;
        if(rhs == Vec{0,0}) return false;

        // y成分が0のケースは例外処理
        if(EQ_EXACT(lhs.y,0) && EQ_EXACT(rhs.y,0)) return lhs.x > 0 && rhs.x < 0;
        if(EQ_EXACT(lhs.y,0)) return lhs.x > 0 || rhs.y < 0;
        if(EQ_EXACT(rhs.y,0)) return lhs.y > 0 && rhs.x < 0;

        // y成分が異符号なら自明
        if(lhs.y < 0 && rhs.y > 0) return false;
        if(lhs.y > 0 && rhs.y < 0) return true;

        // y成分が同符号の場合、外積で判定できる
        return lhs.cross(rhs) > 0;
    }

    friend constexpr Vec operator+(const Vec& lhs, const Vec& rhs) { return Vec(lhs) += rhs; }
    friend constexpr Vec operator-(const Vec& lhs, const Vec& rhs) { return Vec(lhs) -= rhs; }
    friend constexpr Vec operator*(const Vec& lhs, Real rhs) { return Vec(lhs) *= rhs; }
    friend constexpr Vec operator*(Real lhs, const Vec& rhs) { return Vec(rhs) *= lhs; }
    friend constexpr Vec operator/(const Vec& lhs, Real rhs) { return Vec(lhs) /= rhs; }

    friend constexpr bool operator==(const Vec& lhs, const Vec& rhs) {
        return EQ_EXACT(lhs.x,rhs.x) && EQ_EXACT(lhs.y,rhs.y);
    }
    friend constexpr bool operator!=(const Vec& lhs, const Vec& rhs) { return !(lhs == rhs); }

    friend constexpr bool operator<(const Vec& lhs, const Vec& rhs) {
        return make_pair(lhs.x,lhs.y) < make_pair(rhs.x,rhs.y);
    }
};

constexpr bool EQ_EPS(const Vec& lhs, const Vec& rhs, Real eps=EPS) {
    return EQ_EPS(lhs.x,rhs.x,eps) && EQ_EPS(lhs.y,rhs.y,eps);
}

template<>
struct Scan<Vec> {
    static Vec scan(istream& in) {
        Real x = Scan<Real>::scan(in);
        Real y = Scan<Real>::scan(in);
        return {x,y};
    }
};

template<>
struct Fmt<Vec> {
    static void fmt(ostream& out, const Vec& v) {
        fmt_write(out, v.x);
        out << ' ';
        fmt_write(out, v.y);
    }
};

template<>
struct Dbg<Vec> {
    static void dbg(ostream& out, const Vec& v) {
        out << "(";
        dbg_write(out, v.x);
        out << ",";
        dbg_write(out, v.y);
        out << ")";
    }
};

bool geo_is_orthogonal(const Vec& v0, const Vec& v1) {
    return EQ_EPS(v0.dot(v1), 0);
}

bool geo_is_parallel(const Vec& v0, const Vec& v1) {
    return EQ_EPS(v0.cross(v1), 0);
}

enum GeoCcw {
    GEO_CCW_CCW   =  1,
    GEO_CCW_CW    = -1,
    GEO_CCW_BACK  =  2,  // p2--p0--p1 on line
    GEO_CCW_FRONT = -2,  // p0--p1--p2 on line
    GEO_CCW_ON    =  0,  // p0--p2--p1 on line
};

GeoCcw geo_ccw(const Vec& p0, const Vec& p1, const Vec& p2) {
    auto va = p1 - p0;
    auto vb = p2 - p0;

    auto cross = va.cross(vb);
    if(GT_EPS(cross, 0))             return GEO_CCW_CCW;
    if(LT_EPS(cross, 0))             return GEO_CCW_CW;
    if(LT_EPS(va.dot(vb), 0))        return GEO_CCW_BACK;
    if(LT_EPS(va.norm(), vb.norm())) return GEO_CCW_FRONT;
    return GEO_CCW_ON;
}

struct Segment {
    array<Vec,2> p;

    Segment(const Vec& p0, const Vec& p1) : p{p0,p1} {}
    Segment(Real x0, Real y0, Real x1, Real y1) : p{Vec{x0,y0},Vec{x1,y1}} {}

    const Vec& operator[](Int i) const { return p[i]; }
          Vec& operator[](Int i)       { return p[i]; }

    Vec vec() const { return p[1]-p[0]; }

    Real norm() const { return vec().norm(); }
    Real abs() const { return vec().abs(); }
};

template<>
struct Dbg<Segment> {
    static void dbg(ostream& out, const Segment& s) {
        out << "(";
        dbg_write(out, s[0]);
        out << ",";
        dbg_write(out, s[1]);
        out << ")";
    }
};

struct Line {
    array<Vec,2> p;

    Line(const Vec& p0, const Vec& p1) : p{p0,p1} {}
    Line(Real x0, Real y0, Real x1, Real y1) : p{Vec{x0,y0},Vec{x1,y1}} {}
    explicit Line(const Segment& seg) : p{seg.p} {}

    const Vec& operator[](Int i) const { return p[i]; }
          Vec& operator[](Int i)       { return p[i]; }

    Vec vec() const { return p[1]-p[0]; }
};

template<>
struct Dbg<Line> {
    static void dbg(ostream& out, const Line& l) {
        out << "(";
        dbg_write(out, l[0]);
        out << ",";
        dbg_write(out, l[1]);
        out << ")";
    }
};

Vec geo_project(const Line& l, const Vec& p) {
    auto base = l.vec();
    Real r = base.dot(p-l[0]) / base.norm();
    return l[0] + r*base;
}

Vec geo_reflect(const Line& l, const Vec& p) {
    return 2*geo_project(l,p) - p;
}

bool geo_intersects(const Vec& p0, const Vec& p1) {
    return EQ_EPS(p0, p1);
}

bool geo_intersects(const Vec& p, const Line& l) {
    return geo_is_parallel(l[0]-p, l[1]-p);
}
bool geo_intersects(const Line& l, const Vec& p) { return geo_intersects(p,l); }

bool geo_intersects(const Vec& p, const Segment& s) {
    if(!geo_intersects(p, Line(s))) return false;
    auto v = s.vec();
    auto dot0 = (p-s[0]).dot(v);
    auto dot1 = (p-s[1]).dot(-v);
    return !LT_EPS(dot0,0) && !LT_EPS(dot1,0);
}
bool geo_intersects(const Segment& s, const Vec& p) { return geo_intersects(p,s); }

bool geo_intersects(const Line& l0, const Line& l1) {
    if(!geo_is_parallel(l0.vec(), l1.vec())) return true;
    return geo_intersects(l1[0], l0);
}

bool geo_intersects(const Line& l, const Segment& s) {
    auto v = l.vec();
    auto cross0 = v.cross(s[0]-l[0]);
    auto cross1 = v.cross(s[1]-l[0]);
    return !GT_EPS(cross0*cross1, 0);
}
bool geo_intersects(const Segment& s, const Line& l) { return geo_intersects(l,s); }

bool geo_intersects(const Segment& s0, const Segment& s1) {
    if(GT_EPS(geo_ccw(s0[0],s0[1],s1[0])*geo_ccw(s0[0],s0[1],s1[1]), 0)) return false;
    if(GT_EPS(geo_ccw(s1[0],s1[1],s0[0])*geo_ccw(s1[0],s1[1],s0[1]), 0)) return false;
    return true;
}

Real geo_distance(const Vec& p0, const Vec& p1) {
    return (p1-p0).abs();
}

Real geo_distance(const Vec& p, const Line& l) {
    auto v = l.vec();
    return ABS(v.cross(p-l[0]) / v.abs());
}
Real geo_distance(const Line& l, const Vec& p) { return geo_distance(p,l); }

Real geo_distance(const Vec& p, const Segment& s) {
    auto v = s.vec();
    if( v.dot(p-s[0]) < 0) return geo_distance(s[0], p);
    if(-v.dot(p-s[1]) < 0) return geo_distance(s[1], p);
    return geo_distance(p, Line(s));
}
Real geo_distance(const Segment& s, const Vec& p) { return geo_distance(p,s); }

Real geo_distance(const Line& l0, const Line& l1) {
    if(geo_intersects(l0,l1)) return 0;
    return geo_distance(l0[0], l1);
}

Real geo_distance(const Line& l, const Segment& s) {
    if(geo_intersects(l,s)) return 0;
    return MIN(geo_distance(s[0],l), geo_distance(s[1],l));
}
Real geo_distance(const Segment& s, const Line& l) { return geo_distance(l,s); }

Real geo_distance(const Segment& s0, const Segment& s1) {
    if(geo_intersects(s0,s1)) return 0;
    return MIN({
        geo_distance(s0[0], s1),
        geo_distance(s0[1], s1),
        geo_distance(s1[0], s0),
        geo_distance(s1[1], s0),
    });
}

Vec geo_crosspoint(const Line& l0, const Line& l1) {
    ASSERT_LOCAL(geo_intersects(l0,l1));
    auto v0 = l0.vec();
    auto v1 = l1.vec();
    auto a = v0.cross(v1);
    auto b = v0.cross(l0[1]-l1[0]);
    if(EQ_EPS(a,0)) return l0[0];  // 一致
    return l1[0] + b/a*v1;
}

Vec geo_crosspoint(const Line& l, const Segment& s) {
    ASSERT_LOCAL(geo_intersects(l,s));
    return geo_crosspoint(l,Line(s));
}
Vec geo_crosspoint(const Segment& s, const Line& l) { return geo_crosspoint(l,s); }

Vec geo_crosspoint(const Segment& s0, const Segment& s1) {
    ASSERT_LOCAL(geo_intersects(s0,s1));

    if(EQ_EPS(geo_distance(s0[0],s1),0)) return s0[0];
    if(EQ_EPS(geo_distance(s0[1],s1),0)) return s0[1];
    if(EQ_EPS(geo_distance(s1[0],s0),0)) return s1[0];
    if(EQ_EPS(geo_distance(s1[1],s0),0)) return s1[1];

    auto v0 = s0.vec();
    auto v1 = s1.vec();
    auto d0 = ABS(v1.cross(s0[0]-s1[0]));
    auto d1 = ABS(v1.cross(s0[1]-s1[0]));
    auto t = d0 / (d0+d1);
    return s0[0] + t*v0;
}

enum GeoContainment {
    GEO_CONT_OUT,
    GEO_CONT_ON,
    GEO_CONT_IN,
};

bool geo_is_triangle(const Vec& A, const Vec& B, const Vec& C) {
    auto ccw = geo_ccw(A, B, C);
    return ccw == GEO_CCW_CCW || ccw == GEO_CCW_CW;
}

Vec geo_triangle_excenter(const Vec& A, const Vec& B, const Vec& C) {
    ASSERT_LOCAL(geo_is_triangle(A,B,C));

    auto a2 = (B-C).norm();
    auto b2 = (C-A).norm();
    auto c2 = (A-B).norm();

    auto s = a2*(b2+c2-a2);
    auto t = b2*(c2+a2-b2);
    auto u = c2*(a2+b2-c2);
    auto S = ABS((B-A).cross(C-A));

    return (s*A + t*B + u*C) / (4*S*S);
}

struct Polygon {
    vector<Vec> ps;  // 反時計回り

    explicit Polygon(const vector<Vec>& ps_arg) : ps(ps_arg) {}
    explicit Polygon(vector<Vec>&& ps_arg) : ps(ps_arg) {}

    template<class InputIt>
    Polygon(InputIt first, InputIt last) : ps(first,last) {}

    Int size() const { return SIZE(ps); }

    Real area() const {
        Int n = SIZE(ps);
        ASSERT(n >= 3);

        Real res = 0;
        REP(i, n) {
            res += ps[i].cross(ps[(i+1)%n]);
        }
        res /= 2;
        return res;
    }

    bool is_convex() const {
        Int n = SIZE(ps);
        ASSERT(n >= 3);

        REP(i, n) {
            if(geo_ccw(ps[modulo(i-1,n)], ps[i], ps[(i+1)%n]) == GEO_CCW_CW) return false;
        }
        return true;
    }

    GeoContainment containment(const Vec& p) const {
        Int n = SIZE(ps);
        ASSERT(n >= 3);

        Int cnt = 0;
        REP(i, n) {
            Vec a = ps[i] - p;
            Vec b = ps[(i+1)%n] - p;
            if(EQ_EPS(a.cross(b),0) && !GT_EPS(a.dot(b),0)) return GEO_CONT_ON;
            if(a.y > b.y) swap(a, b);
            if(!GT_EPS(a.y,0) && GT_EPS(b.y,0) && GT_EPS(a.cross(b),0)) ++cnt;
        }
        return cnt%2==0 ? GEO_CONT_OUT : GEO_CONT_IN;
    }
};

template<>
struct Dbg<Polygon> {
    static void dbg(ostream& out, const Polygon& poly) {
        dbg_write(out, poly.ps);
    }
};

// 凸包 (Andrew's Monotone Chain)
//
// * 始点はy座標最小のもののうちx座標最小のもの
// * 反時計回り
// * 辺上の点を含む
Polygon geo_convex_hull(vector<Vec> ps) {
    Int n = SIZE(ps);
    ASSERT(n >= 3);

    ALL(sort, ps, LT_ON([](const Vec& p) { return make_pair(p.y,p.x); }));

    auto res = vec_reserve<Vec>(n);
    auto step = [&res](const Vec& p) {
        while(SIZE(res) >= 2) {
            Int k = SIZE(res);
            // 辺上の点を含めたくなければ "!= GEO_CCW_CW" を "== GEO_CCW_CCW" に変える
            if(geo_ccw(res[k-2],res[k-1],p) != GEO_CCW_CW) break;
            res.pop_back();
        }
        res.emplace_back(p);
    };

    // lower hull
    for(Int i = 0; i < n; ++i) {
        step(ps[i]);
    }
    // upper hull
    for(Int i = n-2; i >= 0; --i) {
        step(ps[i]);
    }
    // 始点が重複するので削除
    res.pop_back();

    return Polygon(move(res));
}

template<class InputIt>
Polygon geo_convex_hull(InputIt first, InputIt last) {
    vector<Vec> ps(first, last);
    return geo_convex_hull(move(ps));
}

struct Circle {
    Vec c;
    Real r;

    Circle(const Vec& cc, Real rr) : c(cc), r(rr) {}

    Real circum() const { return 2*PI*r; }
    Real area() const { return PI*r*r; }

    GeoContainment containment(const Vec& p) const {
        auto d = (c-p).abs();
        if(GT_EPS(d,r))
            return GEO_CONT_OUT;
        else if(LT_EPS(d,r))
            return GEO_CONT_IN;
        else
            return GEO_CONT_ON;
    }
};

template<>
struct Dbg<Circle> {
    static void dbg(ostream& out, const Circle& cir) {
        out << "(";
        dbg_write(out, cir.c);
        out << ",";
        dbg_write(out, cir.r);
        out << ")";
    }
};

Int geo_common_tangent_count(const Circle& cir0, const Circle& cir1) {
    Real d = (cir1.c-cir0.c).abs();
    Real rsum = cir0.r + cir1.r;
    Real rdif = ABS(cir0.r - cir1.r);
    if(EQ_EPS(d,rsum)) return 3;    // 外接
    if(rsum < d) return 4;              // 離れている
    if(EQ_EPS(d,rdif)) return 1;    // 内接
    if(rdif < d && d < rsum) return 2;  // 交わる
    return 0;                           // 一方が他方を含む
}

bool geo_intersects(const Vec& p, const Circle& cir) {
    return EQ_EPS((p-cir.c).abs(), cir.r);
}
bool geo_intersects(const Circle& cir, const Vec& p) { return geo_intersects(p,cir); }

bool geo_intersects(const Line& l, const Circle& cir) {
    return !GT_EPS(geo_distance(l,cir.c), cir.r);
}
bool geo_intersects(const Circle& cir, const Line& l) { return geo_intersects(l,cir); }

bool geo_intersects(const Segment& s, const Circle& cir) {
    if(GT_EPS(geo_distance(cir.c,s), cir.r)) return false;
    return !LT_EPS((cir.c-s[0]).abs(), cir.r) || !LT_EPS((cir.c-s[1]).abs(), cir.r);
}
bool geo_intersects(const Circle& cir, const Segment& s) { return geo_intersects(s,cir); }

bool geo_intersects(const Circle& cir0, const Circle& cir1) {
    Int k = geo_common_tangent_count(cir0, cir1);
    return 1 <= k && k <= 3;
}

auto geo_crosspoints(const Line& l, const Circle& cir) {
    ASSERT_LOCAL(geo_intersects(l,cir));

    auto pr = geo_project(l, cir.c);
    auto e  = l.vec().unit();
    auto t  = sqrt(cir.r*cir.r - (pr-cir.c).norm());
    return array<Vec,2> { pr+t*e, pr-t*e };
}
auto geo_crosspoints(const Circle& cir, const Line& l) { return geo_crosspoints(l,cir); }

auto geo_crosspoints(const Circle& cir0, const Circle& cir1) {
    ASSERT_LOCAL(geo_intersects(cir0,cir1));

    auto v = cir1.c - cir0.c;
    auto d = v.abs();
    auto ta = (d*d + cir0.r*cir0.r - cir1.r*cir1.r) / (2*d);
    auto tb = sqrt(MAX(0.0, cir0.r*cir0.r - ta*ta));
    auto vn = v.rotate90();
    return array<Vec,2> {
        cir0.c + ta/d*v + tb/d*vn,
        cir0.c + ta/d*v - tb/d*vn,
    };
}

auto geo_tangent(const Circle& cir, const Vec& p) {
    ASSERT_LOCAL(cir.containment(p) == GEO_CONT_OUT);

    Circle cir1(p, sqrt((cir.c-p).norm() - cir.r*cir.r));
    return geo_crosspoints(cir, cir1);
}

Circle geo_min_ball(vector<Vec> ps) {
    Int n = SIZE(ps);
    ASSERT(n >= 1);
    if(n == 1) return {ps[0],0};

    ALL(shuffle, ps, PROCON_URBG());

    auto f_cir2 = [](const Vec& A, const Vec& B) -> pair<Vec,Real> {
        Vec c = (A+B) / 2;
        Real r2 = (A-c).norm();
        return {c,r2};
    };
    auto f_cir3 = [](const Vec& A, const Vec& B, const Vec& C) -> pair<Vec,Real> {
        Vec c = geo_triangle_excenter(A, B, C);
        Real r2 = (A-c).norm();
        return {c,r2};
    };
    auto f_in = [](const pair<Vec,Real>& cir, const Vec& p) {
        auto c  = cir.first;
        auto r2 = cir.second;
        return !GT_EPS((p-c).norm(), r2);
    };

    auto cir = f_cir2(ps[0], ps[1]);
    FOR(i, 2, n) {
        if(f_in(cir, ps[i])) continue;
        cir = f_cir2(ps[0], ps[i]);
        FOR(j, 1, i) {
            if(f_in(cir, ps[j])) continue;
            cir = f_cir2(ps[i], ps[j]);
            REP(k, j) {
                if(f_in(cir, ps[k])) continue;
                cir = f_cir3(ps[i], ps[j], ps[k]);
            }
        }
    }

    return {cir.first, sqrt(cir.second)};
}

// }}}
