// runtime modint {{{
template<i64 I>
struct RtModIntT {
    static i64 M;

    static i64 get_mod() { return M; }
    static void set_mod(i64 m) { M = m; }

    i64 v_;  // [0,M)

    RtModIntT() : v_(0) {}
    RtModIntT(i64 v) {
        i64 r = v % M;
        v_ = r >= 0 ? r : r+M;
    }

    RtModIntT operator-() const {
        return RtModIntT(-v_);
    }
    RtModIntT& operator+=(RtModIntT rhs) {
        v_ += rhs.v_;
        v_ %= M;
        return *this;
    }
    RtModIntT& operator-=(RtModIntT rhs) {
        v_ += M;
        v_ -= rhs.v_;
        v_ %= M;
        return *this;
    }
    RtModIntT& operator*=(RtModIntT rhs) {
        v_ *= rhs.v_;
        v_ %= M;
        return *this;
    }

    RtModIntT& operator++() {
        return *this += 1;
    }
    RtModIntT& operator--() {
        return *this -= 1;
    }
    RtModIntT operator++(int) {
        return exchange(*this, *this+1);
    }
    RtModIntT operator--(int) {
        return exchange(*this, *this-1);
    }

    explicit operator i64() const { return v_; }
};
template<i64 I>
i64 RtModIntT<I>::M;

template<i64 I>
RtModIntT<I> operator+(RtModIntT<I> lhs, RtModIntT<I> rhs) { return RtModIntT<I>(lhs) += rhs; }
template<i64 I>
RtModIntT<I> operator+(RtModIntT<I> lhs, i64 rhs) { return RtModIntT<I>(lhs) += rhs; }
template<i64 I>
RtModIntT<I> operator+(i64 lhs, RtModIntT<I> rhs) { return RtModIntT<I>(rhs) += lhs; }
template<i64 I>
RtModIntT<I> operator-(RtModIntT<I> lhs, RtModIntT<I> rhs) { return RtModIntT<I>(lhs) -= rhs; }
template<i64 I>
RtModIntT<I> operator-(RtModIntT<I> lhs, i64 rhs) { return RtModIntT<I>(lhs) -= rhs; }
template<i64 I>
RtModIntT<I> operator-(i64 lhs, RtModIntT<I> rhs) { return RtModIntT<I>(rhs) -= lhs; }
template<i64 I>
RtModIntT<I> operator*(RtModIntT<I> lhs, RtModIntT<I> rhs) { return RtModIntT<I>(lhs) *= rhs; }
template<i64 I>
RtModIntT<I> operator*(RtModIntT<I> lhs, i64 rhs) { return RtModIntT<I>(lhs) *= rhs; }
template<i64 I>
RtModIntT<I> operator*(i64 lhs, RtModIntT<I> rhs) { return RtModIntT<I>(rhs) *= lhs; }

template<i64 I>
bool operator==(RtModIntT<I> lhs, RtModIntT<I> rhs) { return lhs.v_ == rhs.v_; }
template<i64 I>
bool operator==(RtModIntT<I> lhs, i64 rhs) { return lhs == RtModIntT<I>(rhs); }
template<i64 I>
bool operator==(i64 lhs, RtModIntT<I> rhs) { return RtModIntT<I>(lhs) == rhs; }
template<i64 I>
bool operator!=(RtModIntT<I> lhs, RtModIntT<I> rhs) { return !(lhs == rhs); }
template<i64 I>
bool operator!=(RtModIntT<I> lhs, i64 rhs) { return !(lhs == rhs); }
template<i64 I>
bool operator!=(i64 lhs, RtModIntT<I> rhs) { return !(lhs == rhs); }

#if 0
template<i64 I>
struct Scan<RtModIntT<I>> {
    static RtModIntT<I> scan(istream& in) {
        return Scan<i64>::scan(in);
    }
};

template<i64 I>
struct Fmt<RtModIntT<I>> {
    static void fmt(ostream& out, RtModIntT<I> x) {
        fmt_write(out, x.v_);
    }
};

template<i64 I>
struct Dbg<RtModIntT<I>> {
    static void dbg(ostream& out, RtModIntT<I> x) {
        dbg_write(out, x.v_);
    }
};
#endif
// }}}
