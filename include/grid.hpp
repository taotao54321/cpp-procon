// grid {{{

template<typename T> struct procon_hash;
template<typename T> void procon_hash_combine(size_t&, const T&);

struct Index2 {
    i64 y, x;

    constexpr Index2() : Index2(0,0) {}
    constexpr Index2(i64 yy, i64 xx) : y(yy), x(xx) {}
    constexpr explicit Index2(const pair<i64,i64>& p) : Index2(p.first,p.second) {}

    static const Index2 DIR4[4];
    static const Index2 DIR8[8];

    Index2 operator-() const {
        return Index2(-y,-x);
    }
    Index2& operator+=(const Index2& rhs) {
        y += rhs.y;
        x += rhs.x;
        return *this;
    }
    Index2& operator-=(const Index2& rhs) {
        y -= rhs.y;
        x -= rhs.x;
        return *this;
    }
    Index2& operator*=(i64 rhs) {
        y *= rhs;
        x *= rhs;
        return *this;
    }
    Index2& operator/=(i64 rhs) {
        y /= rhs;
        x /= rhs;
        return *this;
    }

    i64 norm1() const { return ABS(y) + ABS(x); }

    vector<Index2> neighbor4() const {
        return {
            { y-1, x   },
            { y  , x-1 },
            { y  , x+1 },
            { y+1, x   },
        };
    }
    vector<Index2> neighbor8() const {
        return {
            { y-1, x-1 },
            { y-1, x   },
            { y-1, x+1 },
            { y  , x-1 },
            { y  , x+1 },
            { y+1, x-1 },
            { y+1, x   },
            { y+1, x+1 },
        };
    }
};
const Index2 Index2::DIR4[4] {
            {-1,0},
    {0,-1},         {0,1},
            { 1,0}
};
const Index2 Index2::DIR8[8] {
    {-1,-1}, {-1,0}, {-1,1},
    { 0,-1},         { 0,1},
    { 1,-1}, { 1,0}, { 1,1}
};

Index2 operator+(const Index2& lhs, const Index2& rhs) { return Index2(lhs) += rhs; }
Index2 operator-(const Index2& lhs, const Index2& rhs) { return Index2(lhs) -= rhs; }
Index2 operator*(const Index2& lhs, i64 rhs) { return Index2(lhs) *= rhs; }
Index2 operator*(i64 lhs, const Index2& rhs) { return Index2(rhs) *= lhs; }
Index2 operator/(const Index2& lhs, i64 rhs) { return Index2(lhs) /= rhs; }

bool operator==(const Index2& lhs, const Index2& rhs) {
    return lhs.y == rhs.y && lhs.x == rhs.x;
}
bool operator!=(const Index2& lhs, const Index2& rhs) {
    return !(lhs == rhs);
}

template<>
struct procon_hash<Index2> {
    size_t operator()(const Index2& idx) const {
        size_t seed = 0;
        procon_hash_combine(seed, idx.y);
        procon_hash_combine(seed, idx.x);
        return seed;
    }
};

template<>
struct Scanner<Index2> {
    static Index2 read(istream& in) {
        i64 y = READ<i64>(in);
        i64 x = READ<i64>(in);
        return {y,x};
    }
    static Index2 read1(istream& in) {
        i64 y = READ1<i64>(in);
        i64 x = READ1<i64>(in);
        return {y,x};
    }
};

template<>
struct Formatter<Index2> {
    static ostream& write_str(ostream& out, const Index2& idx) {
        WRITE_STR(out, idx.y);
        out << ' ';
        WRITE_STR(out, idx.x);
        return out;
    }
    static ostream& write_repr(ostream& out, const Index2& idx) {
        out << "(";
        WRITE_REPR(out, idx.y);
        out << ",";
        WRITE_REPR(out, idx.x);
        out << ")";
        return out;
    }
};

template<typename T>
struct Grid2 {
    using InnerT = typename Array1Container<T>::type;
    vector<InnerT> cont_;

    Grid2(i64 h, i64 w, const T& val) : cont_(arrayn_make<T>(h,w, val)) {
        ASSERT(h >= 1);
        ASSERT(w >= 1);
    }
    Grid2(i64 h, i64 w) : Grid2(h, w, T()) {}

    i64 h() const { return SIZE(cont_);    }
    i64 w() const { return SIZE(cont_[0]); }

          T& operator[](const Index2& idx)       { return at(idx.y, idx.x); }
    const T& operator[](const Index2& idx) const { return at(idx.y, idx.x); }

          T& at(i64 y, i64 x)       { return cont_[y][x]; }
    const T& at(i64 y, i64 x) const { return cont_[y][x]; }

    bool idx_is_valid(const Index2& idx) const { return idx_is_valid(idx.y, idx.x); }
    bool idx_is_valid(i64 y, i64 x) const {
        return 0 <= y && y < h() && 0 <= x && x < w();
    }

    vector<Index2> neighbor4(const Index2& idx) const {
        vector<Index2> res = idx.neighbor4();
        auto it = ALL(remove_if, res, [this](const auto& to) { return !this->idx_is_valid(to); });
        res.erase(it, end(res));
        return res;
    }
    vector<Index2> neighbor4(i64 y, i64 x) const { return neighbor4({y,x}); }

    vector<Index2> neighbor8(const Index2& idx) const {
        vector<Index2> res = idx.neighbor8();
        auto it = ALL(remove_if, res, [this](const auto& to) { return !this->idx_is_valid(to); });
        res.erase(it, end(res));
        return res;
    }
    vector<Index2> neighbor8(i64 y, i64 x) const { return neighbor8({y,x}); }

    template<typename F>
    void foreach(F f) {
        for(auto& row : cont_)
            for(auto& e : row)
                f(e);
    }

    void fill(const T& x) {
        foreach([&x](auto& e) { e = x; });
    }
};

template<typename T>
auto RD_GRID2(i64 h, i64 w) {
    Grid2<T> grid(h, w);
    REP(y, grid.h()) REP(x, grid.w()) {
        grid.at(y,x) = RD<T>();
    }
    return grid;
}

template<typename T>
auto RD1_GRID2(i64 h, i64 w) {
    Grid2<T> grid(h, w);
    REP(y, grid.h()) REP(x, grid.w()) {
        grid.at(y,x) = RD1<T>();
    }
    return grid;
}

template<typename T>
struct Formatter<Grid2<T>> {
    static ostream& write_str(ostream& out, const Grid2<T>& grid) {
        for(const auto& row : grid.cont_) {
            WRITE_STR(out, row);
            out << "\n";
        }
        return out;
    }
    static ostream& write_repr(ostream& out, const Grid2<T>& grid) {
        out << "\n";
        for(const auto& row : grid.cont_) {
            WRITE_STR(out, row);
            out << "\n";
        }
        out << "\n";
        return out;
    }
};

template<>
struct Formatter<Grid2<char>> {
    static ostream& write_str(ostream& out, const Grid2<char>& grid) {
        for(const auto& row : grid.cont_) {
            ALL(copy, row, ostream_iterator<char>(out));
            out << "\n";
        }
        return out;
    }
    static ostream& write_repr(ostream& out, const Grid2<char>& grid) {
        out << "\n";
        for(const auto& row : grid.cont_) {
            ALL(copy, row, ostream_iterator<char>(out));
            out << "\n";
        }
        out << "\n";
        return out;
    }
};

// }}}
