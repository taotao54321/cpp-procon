struct Vector {
    f64 x, y;

    Vector() : Vector(0,0) {}
    Vector(f64 xx, f64 yy) : x(xx), y(yy) {}

    const Vector operator-() const {
        return Vector(-x,-y);
    }
    Vector& operator+=(const Vector& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vector& operator-=(const Vector& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    Vector& operator*=(f64 rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    Vector& operator/=(f64 rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    f64 norm() const { return x*x + y*y; }
    f64 abs() const { return sqrt(norm()); }

    Vector unit() const { return Vector(*this) /= this->abs(); }
};

const Vector operator+(const Vector& lhs, const Vector& rhs) { return Vector(lhs) += rhs; }
const Vector operator-(const Vector& lhs, const Vector& rhs) { return Vector(lhs) -= rhs; }
const Vector operator*(const Vector& lhs, f64 rhs) { return Vector(lhs) *= rhs; }
const Vector operator*(f64 lhs, const Vector& rhs) { return Vector(rhs) *= lhs; }
const Vector operator/(const Vector& lhs, f64 rhs) { return Vector(lhs) /= rhs; }

bool operator==(const Vector& lhs, const Vector& rhs) {
    return feq(lhs.x,rhs.x) && feq(lhs.y,rhs.y);
}

f64 geo_dot(const Vector& lhs, const Vector& rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

f64 geo_cross(const Vector& lhs, const Vector& rhs) {
    return lhs.x*rhs.y - lhs.y*rhs.x;
}

Vector geo_rotate(const Vector& v, f64 t) {
    return Vector(v.x*cos(t)-v.y*sin(t), v.x*sin(t)+v.y*cos(t));
}

enum ABC {
    ABC_CCW        =  1,
    ABC_CW         = -1,
    ABC_ON_BACK    =  2,
    ABC_ON_FRONT   = -2,
    ABC_ON_SEGMENT =  0,
};

ABC geo_abc(const Vector& a, const Vector& b, const Vector& c) {
    Vector x = b - a;
    Vector y = c - a;
    f64 cross = geo_cross(x,y);
    if(cross > 0) return ABC_CCW;
    if(cross < 0) return ABC_CW;
    f64 dot = geo_dot(x,y);
    if(dot < 0) return ABC_ON_BACK;
    if(x.norm() < y.norm()) return ABC_ON_FRONT;
    return ABC_ON_SEGMENT;
}

enum Containment {
    CONT_IN,
    CONT_ON,
    CONT_OUT,
};

ostream& operator<<(ostream& out, const Vector& v) {
    return out << "Vector(" << v.x << "," << v.y << ")";
}

struct Segment {
    Vector p1, p2;

    Segment(const Vector& pp1, const Vector& pp2) : p1(pp1), p2(pp2) {}
    Segment(f64 x1, f64 y1, f64 x2, f64 y2) : p1(Vector(x1,y1)), p2(Vector(x2,y2)) {}

    Vector vec() const { return p2 - p1; }

    f64 norm() const { return vec().norm(); }
    f64 abs() const { return vec().abs(); }
};

ostream& operator<<(ostream& out, const Segment& seg) {
    out << "Segment(";
    out << "(" << seg.p1.x << "," << seg.p1.y << ")";
    out << ",";
    out << "(" << seg.p2.x << "," << seg.p2.y << ")";
    out << ")";
    return out;
}

struct Line {
    Vector p1, p2;

    Line(const Vector& pp1, const Vector& pp2) : p1(pp1), p2(pp2) {}
    Line(f64 x1, f64 y1, f64 x2, f64 y2) : p1(Vector(x1,y1)), p2(Vector(x2,y2)) {}
    explicit Line(const Segment& seg) : p1(seg.p1), p2(seg.p2) {}

    Vector vec() const { return p2 - p1; }
};

ostream& operator<<(ostream& out, const Line& line) {
    out << "Line(";
    out << "(" << line.p1.x << "," << line.p1.y << ")";
    out << ",";
    out << "(" << line.p2.x << "," << line.p2.y << ")";
    out << ")";
    return out;
}

struct Circle {
    Vector c;
    f64 r;

    Circle(const Vector& cc, f64 rr) : c(cc), r(rr) {}
};

ostream& operator<<(ostream& out, const Circle& cir) {
    out << "Circle(";
    out << "(" << cir.c.x << "," << cir.c.y << ")";
    out << ",";
    out << cir.r;
    out << ")";
    return out;
}

enum CircleRelation {
    CIRS_IN        = 0,
    CIRS_TOUCH_IN  = 1,
    CIRS_CROSS     = 2,
    CIRS_TOUCH_OUT = 3,
    CIRS_OUT       = 4,
    CIRS_SAME      = 5,
};

CircleRelation geo_circle_relation(const Circle& cir1, const Circle& cir2) {
    f64 d = (cir2.c-cir1.c).norm();
    f64 a = pow(cir1.r+cir2.r, 2);
    f64 b = pow(cir1.r-cir2.r, 2);
    if(feq(d, a)) {
        return CIRS_TOUCH_OUT;
    }
    else if(feq(d, b)) {
        return feq(d,0) ? CIRS_SAME : CIRS_TOUCH_IN;
    }
    else if(a < d) {
        return CIRS_OUT;
    }
    else if(b < d && d < a) {
        return CIRS_CROSS;
    }
    else {  // d < b
        return CIRS_IN;
    }
}

struct Polygon {
    vector<Vector> ps;

    explicit Polygon(const vector<Vector>& ps_arg) : ps(ps_arg) {}

    f64 area_2x() const {
        i64 n = SIZE(ps);
        if(n < 3) return 0;
        f64 sum = 0;
        REP(i, n) {
            sum += geo_cross(cur(i), nex(i));
        }
        return fabs(sum);
    }
    f64 area() const { return area_2x() / 2; }

    // 凸性判定(全ての内角が180度以下)
    // 3点が同一直線上にあるケースは許容する(この辺ちょっと怪しい)
    // 2角形以下の場合 false を返す
    bool is_convex() const {
        i64 n = SIZE(ps);
        if(n < 3) return false;
        i64 abc = 0;
        REP(i, n) {
            ABC abc_cur = geo_abc(pre(i), cur(i), nex(i));
            if(abc_cur != ABC_CCW && abc_cur != ABC_CW) continue;
            if(abc_cur*abc == -1) return false;
            abc = abc_cur;
        }
        return true;
    }

    // 点の包含判定
    // 2角形以下の場合 CONT_OUT を返す
    Containment containment(const Vector& p) const {
        i64 n = SIZE(ps);
        if(n < 3) return CONT_OUT;
        i64 cnt = 0;
        REP(i, n) {
            Vector a = cur(i) - p;
            Vector b = nex(i) - p;
            if(feq(geo_cross(a,b),0) && geo_dot(a,b) <= 0) return CONT_ON;
            if(a.y > b.y) swap(a,b);
            if(a.y <= 0 && b.y > 0 && geo_cross(a,b) > 0) ++cnt;
        }
        return is_odd(cnt) ? CONT_IN : CONT_OUT;
    }

    Vector cur(i64 i) const { return ps[i]; }
    Vector pre(i64 i) const { return ps[modulo(i-1,SIZE(ps))]; }
    Vector nex(i64 i) const { return ps[modulo(i+1,SIZE(ps))]; }
};

ostream& operator<<(ostream& out, const Polygon& poly) {
    out << "Polygon(";
    i64 n = SIZE(poly.ps);
    REP(i, n) {
        const Vector& p = poly.ps[i];
        out << "(" << p.x << "," << p.y << ")";
        if(i != n-1)
            out << ",";
    }
    out << ")";
    return out;
}

Vector geo_project(const Line& line, const Vector& p) {
    Vector v = line.vec();
    f64 r = geo_dot(p-line.p1, v) / v.norm();
    return line.p1 + r*v;
}

bool geo_intersect(const Segment& x, const Segment& y) {
    return geo_abc(x.p1,x.p2,y.p1) * geo_abc(x.p1,x.p2,y.p2) <= 0 &&
           geo_abc(y.p1,y.p2,x.p1) * geo_abc(y.p1,y.p2,x.p2) <= 0;
}

bool geo_intersect(const Circle& cir1, const Circle& cir2) {
    return (cir1.c-cir2.c).norm() <= pow(cir1.r+cir2.r,2);
}

f64 geo_distance(const Line& line, const Vector& p) {
    Vector v = line.vec();
    return fabs(geo_cross(v,p-line.p1)) / v.abs();
}

f64 geo_distance(const Segment& seg, const Vector& p) {
    if(geo_dot( seg.vec(), p-seg.p1) < 0) return (p-seg.p1).abs();
    if(geo_dot(-seg.vec(), p-seg.p2) < 0) return (p-seg.p2).abs();
    return geo_distance(Line(seg), p);
}

f64 geo_distance(const Segment& seg1, const Segment& seg2) {
    if(geo_intersect(seg1,seg2)) return 0;
    return min({
        geo_distance(seg1, seg2.p1),
        geo_distance(seg1, seg2.p2),
        geo_distance(seg2, seg1.p1),
        geo_distance(seg2, seg1.p2),
    });
}

bool geo_intersect(const Circle& cir, const Line& line) {
    return geo_distance(line, cir.c) <= cir.r;
}

// 交差判定は既に行われているとする
// FIXME: 2線分が重なる場合を考慮してない
Vector geo_crosspoint(const Segment& seg1, const Segment& seg2) {
    Vector v = seg2.vec();
    f64 d1 = fabs(geo_cross(v, seg1.p1-seg2.p1));
    f64 d2 = fabs(geo_cross(v, seg1.p2-seg2.p1));
    return seg1.p1 + (d1/(d1+d2))*seg1.vec();
}

// 2直線が重なる場合、la.p1 を返す
// 2直線が平行かつ重ならない場合エラー(先に交差判定すること)
Vector geo_crosspoint(const Line& la, const Line& lb) {
    Vector a = la.vec();
    Vector b = lb.vec();
    f64 d1 = geo_cross(b, lb.p1-la.p1);
    f64 d2 = geo_cross(b, a);
    if(feq(d2, 0)) {  // 2直線が平行
        if(feq(d1, 0)) return la.p1;  // 2直線が重なっている
        assert(false);
    }
    return la.p1 + d1/d2*a;
}

// 接する場合も同じ座標2つを返す
vector<Vector> geo_crosspoints(const Circle& cir, const Line& line) {
    if(!geo_intersect(cir,line)) return {};
    Vector p = geo_project(line, cir.c);
    Vector e = line.vec().unit();
    f64 t = sqrt(cir.r*cir.r - (p-cir.c).norm());
    return { p+t*e, p-t*e };
}

// 接する場合も同じ座標2つを返す
vector<Vector> geo_crosspoints(const Circle& cir1, const Circle& cir2) {
    if(!geo_intersect(cir1,cir2)) return {};
    Vector v = cir2.c - cir1.c;
    f64 d = v.abs();
    f64 t = acos((cir1.r*cir1.r + d*d - cir2.r*cir2.r) / (2*cir1.r*d));
    return {
        cir1.c + geo_rotate(v, t) / d * cir1.r,
        cir1.c + geo_rotate(v,-t) / d * cir1.r,
    };
}

// 凸包 (Andrew's Monotone Chain)
//
// * 始点はy座標最小のもののうちx座標最小のもの
// * 反時計回り
// * 辺上の点を含む
Polygon geo_convex_hull(vector<Vector> ps) {
    i64 n = SIZE(ps);
    assert(n >= 3);

    vector<Vector> res;
    res.reserve(n);

    ALL(sort, ps, ON(less<>(), [](const Vector& p) { return make_pair(p.y,p.x); }));

    auto step = [&res](const Vector& p) {
        while(SIZE(res) >= 2) {
            i64 k = SIZE(res);
            // 辺上の点を含めたくなければ "!= ABC_CW" を "== ABC_CCW" に変える
            if(geo_abc(res[k-2],res[k-1],p) != ABC_CW) break;
            res.pop_back();
        }
        res.emplace_back(p);
    };

    // lower hull
    for(i64 i = 0; i < n; ++i) {
        step(ps[i]);
    }
    // upper hull
    for(i64 i = n-2; i >= 0; --i) {
        step(ps[i]);
    }
    // 始点が重複するので削除
    res.pop_back();

    return Polygon(res);
}

// 凸多角形の直径 (Rotating Calipers)
//
// (直径の2乗, index_端点1, index_端点2) を返す
// convex は凸多角形でなければならない
tuple<f64,i64,i64> geo_convex_diameter_sq(const Polygon& convex) {
    const auto& ps = convex.ps;
    i64 n = SIZE(ps);

    auto cmp_y = ON(less<>(), [](const Vector& p) { return p.y; });
    i64 istart = ALL(max_element, ps, cmp_y) - begin(ps);
    i64 jstart = ALL(min_element, ps, cmp_y) - begin(ps);

    auto nex = [n](i64 i) { return modulo(i+1,n); };

    f64 d2max = (ps[istart]-ps[jstart]).norm();
    i64 i, imax, j, jmax;
    i = imax = istart;
    j = jmax = jstart;
    do {
        Vector vi = ps[nex(i)] - ps[i];
        Vector vj = ps[nex(j)] - ps[j];
        if(geo_cross(vi,vj) >= 0)
            j = nex(j);
        else
            i = nex(i);
        if(chmax(d2max, (ps[i]-ps[j]).norm())) {
            imax = i;
            jmax = j;
        }
    } while(i != istart || j != jstart);

    return { d2max, imax, jmax };
    // AOJの場合はこっち
    //return make_tuple(d2max, imax, jmax);
}

// 凸多角形の切断
//
// convex は凸多角形でなければならない
Polygon geo_convex_cut(const Polygon& convex, const Line& line) {
    const vector<Vector>& ps = convex.ps;
    i64 n = SIZE(ps);
    auto nex = [n](i64 i) { return modulo(i+1,n); };

    vector<Vector> res;
    REP(i, n) {
        // ps[i] が直線より左または直線上なら ps[i] を追加
        ABC abc_a = geo_abc(line.p1, line.p2, ps[i]);
        if(abc_a != ABC_CW)
            res.emplace_back(ps[i]);
        // ps[i] が直線より左、かつ ps[i+1] が直線より右なら交点を追加
        ABC abc_b = geo_abc(line.p1, line.p2, ps[nex(i)]);
        if(abc_a*abc_b < 0)
            res.emplace_back(geo_crosspoint(line, Line(ps[i],ps[nex(i)])));
    }
    return Polygon(res);
}

// geo_closest_pair() 下請け
// [first,last) はx座標に関してソート済であること
template<typename RandomIt>
tuple<f64,RandomIt,RandomIt> geo_closest_pair_sq_impl(RandomIt first, RandomIt last) {
    i64 n = last - first;
    if(n <= 1)
        return { DBL_MAX, last, last };
        // AOJの場合はこっち
        //return make_tuple(DBL_MAX, last, last);

    auto mid = first + n/2;
    f64 x = mid->x;
    auto res = min(geo_closest_pair_sq_impl(first,mid), geo_closest_pair_sq_impl(mid,last));
    inplace_merge(first, mid, last, LT_ON([](const Vector& p) { return p.y; }));

    vector<RandomIt> around;
    for(auto i = first; i != last; ++i) {
        f64 d = x - i->x;
        if(d*d >= get<0>(res)) continue;
        for(auto j = around.rbegin(); j != around.rend(); ++j) {
            f64 dx = i->x - (*j)->x;
            f64 dy = i->y - (*j)->y;
            if(dy*dy >= get<0>(res)) break;
            f64 cur = dx*dx + dy*dy;
            if(cur < get<0>(res))
                res = { cur, i, *j };
                // AOJの場合はこっち
                //res = make_tuple(cur, i, *j);
        }
        around.emplace_back(i);
    }

    return res;
}

// 最近点対
//
// (距離の2乗, index_端点1, index_端点2) を返す
// SIZE(ps) < 2 ならエラー
// O(nlogn)
tuple<f64,i64,i64> geo_closest_pair_sq(vector<Vector> ps) {
    assert(SIZE(ps) >= 2);

    ALL(sort, ps, LT_ON([](const Vector& p) { return p.x; }));

    auto res = ALL(geo_closest_pair_sq_impl, ps);
    auto i = get<1>(res) - begin(ps);
    auto j = get<2>(res) - begin(ps);
    return { get<0>(res), i, j };
    // AOJの場合はこっち
    //return make_tuple(get<0>(res), i, j);
}

// p を通る cir の接線 ([0,2] 個)
// 各 Line の p2 が接点となる
vector<Line> geo_tangent(const Circle& cir, const Vector& p) {
    Vector v = cir.c - p;
    f64 d1_sq = v.norm();
    f64 d2_sq = d1_sq - cir.r*cir.r;
    if(d2_sq < 0) return {};

    f64 d1 = sqrt(d1_sq);
    f64 d2 = sqrt(d2_sq);
    f64 cos_a = d2 / d1;
    f64 sin_a = cir.r / d1;

    vector<Line> res;
    Vector w1 {
         v.x*cos_a + v.y*sin_a,
        -v.x*sin_a + v.y*cos_a,
    };
    res.emplace_back(Line(p, p + d2/d1*w1));
    if(feq(d2, 0)) return res;
    Vector w2 {
        v.x*cos_a - v.y*sin_a,
        v.x*sin_a + v.y*cos_a,
    };
    res.emplace_back(Line(p, p + d2/d1*w2));

    return res;
}

void RD(Vector& v) {
    RD(v.x);
    RD(v.y);
}
