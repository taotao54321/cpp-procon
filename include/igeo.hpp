// igeo {{{

struct IVec {
    Int x{}, y{};

    constexpr IVec() = default;
    constexpr IVec(Int xx, Int yy) : x(xx), y(yy) {}

    constexpr IVec operator-() const { return {-x,-y}; }

    constexpr IVec& operator+=(const IVec& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    constexpr IVec& operator-=(const IVec& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    constexpr IVec& operator*=(Int rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    constexpr IVec& operator/=(Int rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    // [(x0,y0),(x1,y1))
    /*constexpr*/ bool is_in(Int x0, Int y0, Int x1, Int y1) const {
        ASSERT_LOCAL(x0 <= x1 && y0 <= y1);
        return x0 <= x && x < x1 && y0 <= y && y < y1;
    }
    /*constexpr*/ bool is_in(const IVec& p0, const IVec& p1) const {
        ASSERT_LOCAL(p0.x <= p1.x && p0.y <= p1.y);
        return p0.x <= x && x < p1.x && p0.y <= y && y < p1.y;
    }

    template<class C>
    constexpr const auto& operator[](const C& cont) const { return cont[y][x]; }
    template<class C>
    constexpr       auto& operator[](C& cont) const { return cont[y][x]; }

    constexpr Int norm() const { return x*x + y*y; }

    constexpr Int dot(const IVec& rhs) const {
        return x*rhs.x + y*rhs.y;
    }

    constexpr Int cross(const IVec& rhs) const {
        return x*rhs.y - y*rhs.x;
    }

    constexpr IVec rotate90() const {
        return {-y,x};
    }

    static constexpr bool lt_arg(const IVec& lhs, const IVec& rhs) {
        // 零ベクトルは偏角最小とみなす
        if(lhs == rhs) return false;
        if(lhs == IVec{0,0}) return true;
        if(rhs == IVec{0,0}) return false;

        // y成分が0のケースは例外処理
        if(lhs.y == 0 && rhs.y == 0) return lhs.x > 0 && rhs.x < 0;
        if(lhs.y == 0) return lhs.x > 0 || rhs.y < 0;
        if(rhs.y == 0) return lhs.y > 0 && rhs.x < 0;

        // y成分が異符号なら自明
        if(lhs.y < 0 && rhs.y > 0) return false;
        if(lhs.y > 0 && rhs.y < 0) return true;

        // y成分が同符号の場合、外積で判定できる
        return lhs.cross(rhs) > 0;
    }

    friend constexpr IVec operator+(const IVec& lhs, const IVec& rhs) { return IVec(lhs) += rhs; }
    friend constexpr IVec operator-(const IVec& lhs, const IVec& rhs) { return IVec(lhs) -= rhs; }
    friend constexpr IVec operator*(const IVec& lhs, Int rhs) { return IVec(lhs) *= rhs; }
    friend constexpr IVec operator*(Int lhs, const IVec& rhs) { return IVec(rhs) *= lhs; }
    friend constexpr IVec operator/(const IVec& lhs, Int rhs) { return IVec(lhs) /= rhs; }

    friend constexpr bool operator==(const IVec& lhs, const IVec& rhs) {
        return lhs.x==rhs.x && lhs.y==rhs.y;
    }
    friend constexpr bool operator!=(const IVec& lhs, const IVec& rhs) { return !(lhs == rhs); }
};

template<>
struct Scan<IVec> {
    static IVec scan(istream& in) {
        Int x = Scan<Int>::scan(in);
        Int y = Scan<Int>::scan(in);
        return {x,y};
    }
};

template<>
struct Fmt<IVec> {
    static void fmt(ostream& out, const IVec& v) {
        fmt_write(out, v.x);
        out << ' ';
        fmt_write(out, v.y);
    }
};

template<>
struct Dbg<IVec> {
    static void dbg(ostream& out, const IVec& v) {
        out << "(";
        dbg_write(out, v.x);
        out << ",";
        dbg_write(out, v.y);
        out << ")";
    }
};

// }}}
