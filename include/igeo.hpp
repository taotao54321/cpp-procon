// igeo {{{

struct IVec {
    i64 x{}, y{};

    constexpr IVec() = default;
    constexpr IVec(i64 xx, i64 yy) : x(xx), y(yy) {}

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
    constexpr IVec& operator*=(i64 rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    constexpr IVec& operator/=(i64 rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    template<class C>
    constexpr const auto& operator[](const C& cont) const { return cont[y][x]; }
    template<class C>
    constexpr       auto& operator[](C& cont) const { return cont[y][x]; }

    constexpr i64 norm() const { return x*x + y*y; }

    constexpr i64 dot(const IVec& rhs) const {
        return x*rhs.x + y*rhs.y;
    }

    constexpr i64 cross(const IVec& rhs) const {
        return x*rhs.y - y*rhs.x;
    }

    constexpr IVec rotate90() const {
        return {-y,x};
    }

    constexpr static bool lt_arg(const IVec& lhs, const IVec& rhs) {
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
    friend constexpr IVec operator*(const IVec& lhs, i64 rhs) { return IVec(lhs) *= rhs; }
    friend constexpr IVec operator*(i64 lhs, const IVec& rhs) { return IVec(rhs) *= lhs; }
    friend constexpr IVec operator/(const IVec& lhs, i64 rhs) { return IVec(lhs) /= rhs; }

    friend constexpr bool operator==(const IVec& lhs, const IVec& rhs) {
        return lhs.x==rhs.x && lhs.y==rhs.y;
    }
    friend constexpr bool operator!=(const IVec& lhs, const IVec& rhs) { return !(lhs == rhs); }
};

template<>
struct Scan<IVec> {
    static IVec scan(istream& in) {
        i64 x = Scan<i64>::scan(in);
        i64 y = Scan<i64>::scan(in);
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
