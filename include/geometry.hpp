struct Vector {
    f64 x, y;

    Vector() : Vector(0.0,0.0) {}
    Vector(f64 xx, f64 yy) : x(xx), y(yy) {}

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
};

const Vector operator+(const Vector& lhs, const Vector& rhs) { return Vector(lhs) += rhs; }
const Vector operator-(const Vector& lhs, const Vector& rhs) { return Vector(lhs) -= rhs; }
const Vector operator*(const Vector& lhs, f64 rhs) { return Vector(lhs) *= rhs; }
const Vector operator*(f64 lhs, const Vector& rhs) { return Vector(rhs) *= lhs; }
const Vector operator/(const Vector& lhs, f64 rhs) { return Vector(lhs) /= rhs; }

bool operator==(const Vector& lhs, const Vector& rhs) {
    return feq(lhs.x,rhs.x) && feq(lhs.y,rhs.y);
}

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
    Line(const Segment& seg) : p1(seg.p1), p2(seg.p2) {}

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

f64 geo_dot(const Vector& lhs, const Vector& rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

f64 geo_cross(const Vector& lhs, const Vector& rhs) {
    return lhs.x*rhs.y - lhs.y*rhs.x;
}

Vector geo_project(const Line& line, const Vector& p) {
    Vector v = line.vec();
    f64 r = geo_dot(p-line.p1, v) / v.norm();
    return line.p1 + r*v;
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

bool geo_intersect(const Segment& x, const Segment& y) {
    return geo_abc(x.p1,x.p2,y.p1) * geo_abc(x.p1,x.p2,y.p2) <= 0 &&
           geo_abc(y.p1,y.p2,x.p1) * geo_abc(y.p1,y.p2,x.p2) <= 0;
}

f64 geo_distance(const Line& line, const Vector& p) {
    Vector v = line.vec();
    return fabs(geo_cross(v,p-line.p1)) / v.abs();
}

Vector geo_crosspoint(const Segment& x, const Segment& y) {
    Line ly = Line(y);
    f64 d1 = geo_distance(ly, x.p1);
    f64 d2 = geo_distance(ly, x.p2);
    return x.p1 + (d1/(d1+d2))*x.vec();
}

void RD(Vector& v) {
    RD(v.x);
    RD(v.y);
}
