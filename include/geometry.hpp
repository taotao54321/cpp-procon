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

struct Line {
    Vector p1, p2;

    Line(const Vector& pp1, const Vector& pp2) : p1(pp1), p2(pp2) {}
    Line(f64 x1, f64 y1, f64 x2, f64 y2) : p1(Vector(x1,y1)), p2(Vector(x2,y2)) {}

    Vector vec() const { return p2 - p1; }
};

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

bool geo_intersect(const Vector& p1, const Vector& p2, const Vector& p3, const Vector& p4) {
    return geo_abc(p1,p2,p3) * geo_abc(p1,p2,p4) <= 0 &&
           geo_abc(p3,p4,p1) * geo_abc(p3,p4,p2) <= 0;
}

void RD(Vector& v) {
    RD(v.x);
    RD(v.y);
}
