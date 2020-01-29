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
};

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

bool geo_is_orthogonal(const Vec& v0, const Vec& v1, Real eps=EPS) {
    return EQ_EPS(v0.dot(v1), 0, eps);
}

bool geo_is_parallel(const Vec& v0, const Vec& v1, Real eps=EPS) {
    return EQ_EPS(v0.cross(v1), 0, eps);
}

/**
 * +1: ccw
 * -1: cw
 * +2: p2--p0--p1 on line
 * -2: p0--p1--p2 on line
 *  0: p0--p2--p1 on line
 */
i64 geo_ccw(const Vec& p0, const Vec& p1, const Vec& p2, Real eps=EPS) {
    auto va = p1 - p0;
    auto vb = p2 - p0;

    auto cross = va.cross(vb);
    if(GT_EPS(cross, 0, eps))             return  1;
    if(LT_EPS(cross, 0, eps))             return -1;
    if(LT_EPS(va.dot(vb), 0, eps))        return  2;
    if(LT_EPS(va.norm(), vb.norm(), eps)) return -2;
    return 0;
}

struct Segment {
    array<Vec,2> p;

    Segment(const Vec& p0, const Vec& p1) : p{p0,p1} {}
    Segment(Real x0, Real y0, Real x1, Real y1) : p{Vec{x0,y0},Vec{x1,y1}} {}

    const Vec& operator[](i64 i) const { return p[i]; }
          Vec& operator[](i64 i)       { return p[i]; }

    Vec vec() const { return p[1]-p[0]; }

    Real norm() const { return vec().norm(); }
    Real abs() const { return vec().abs(); }
};

struct Line {
    array<Vec,2> p;

    Line(const Vec& p0, const Vec& p1) : p{p0,p1} {}
    Line(Real x0, Real y0, Real x1, Real y1) : p{Vec{x0,y0},Vec{x1,y1}} {}
    explicit Line(const Segment& seg) : p{seg.p} {}

    const Vec& operator[](i64 i) const { return p[i]; }
          Vec& operator[](i64 i)       { return p[i]; }

    Vec vec() const { return p[1]-p[0]; }
};

bool geo_intersects(const Vec& p0, const Vec& p1, Real eps=EPS) {
    return EQ_EPS((p1-p0).norm(), 0, eps);
}

bool geo_intersects(const Vec& p, const Line& l, Real eps=EPS) {
    return geo_is_parallel(l[0]-p, l[1]-p, eps);
}
bool geo_intersects(const Line& l, const Vec& p, Real eps=EPS) { return geo_intersects(p,l,eps); }

bool geo_intersects(const Vec& p, const Segment& s, Real eps=EPS) {
    if(!geo_intersects(p, Line(s))) return false;
    auto v = s.vec();
    auto dot0 = (p-s[0]).dot(v);
    auto dot1 = (p-s[1]).dot(-v);
    return !LT_EPS(dot0,0,eps) && !LT_EPS(dot1,0,eps);
}
bool geo_intersects(const Segment& s, const Vec& p, Real eps=EPS) { return geo_intersects(p,s,eps); }

bool geo_intersects(const Line& l0, const Line& l1, Real eps=EPS) {
    if(!geo_is_parallel(l0.vec(), l1.vec(), eps)) return true;
    return geo_intersects(l1[0], l0);
}

bool geo_intersects(const Line& l, const Segment& s, Real eps=EPS) {
    auto v = l.vec();
    auto cross0 = v.cross(s[0]-l[0]);
    auto cross1 = v.cross(s[1]-l[0]);
    return !GT_EPS(cross0*cross1, 0, eps);
}
bool geo_intersects(const Segment& s, const Line& l, Real eps=EPS) { return geo_intersects(l,s,eps); }

bool geo_intersects(const Segment& s0, const Segment& s1, Real eps=EPS) {
    if(GT_EPS(geo_ccw(s0[0],s0[1],s1[0])*geo_ccw(s0[0],s0[1],s1[1]), 0, eps)) return false;
    if(GT_EPS(geo_ccw(s1[0],s1[1],s0[0])*geo_ccw(s1[0],s1[1],s0[1]), 0, eps)) return false;
    return true;
}

// }}}
