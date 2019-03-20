// {{{ num

// 事前条件: a >= 0, b >= 0
i64 gcd_impl(i64 a, i64 b) {
    if(b == 0) return a;
    return gcd_impl(b, a%b);
}

// gcd(0,0) = 0
i64 gcd(i64 a, i64 b) {
    return gcd_impl(abs(a), abs(b));
}

// lcm(0,x) は未定義
i64 lcm(i64 a, i64 b) {
    assert(a != 0 && b != 0);
    a = abs(a);
    b = abs(b);
    return a / gcd_impl(a,b) * b;
}

// 事前条件: a >= 0, b >= 0
i64 extgcd_impl(i64 a, i64 b, i64& x, i64& y) {
    if(b == 0) {
        x = 1; y = 0;
        return a;
    }
    i64 g = extgcd_impl(b, a%b, y, x);
    y -= a/b * x;
    return g;
}

// g=gcd(a,b), および ax+by=g の整数解 (x0,y0) を求める
// (g,x0,y0) を返す
// g!=0 のとき、一般解は (x,y) = (x0+m*b/g, y0-m*a/g) で与えられる(mは整数)
tuple<i64,i64,i64> extgcd(i64 a, i64 b) {
    i64 x, y;
    i64 g = extgcd_impl(abs(a), abs(b), x, y);
    x *= sgn(a);
    y *= sgn(b);
    return make_tuple(g, x, y);
}

// 素因数分解
// (素因数,指数) のリストを返す
// n >= 1 でなければならない
// n == 1 の場合、空リストを返す
vector<pair<i64,i64>> factorize(i64 n) {
    assert(n >= 1);

    vector<pair<i64,i64>> res;

    i64 m = n;
    for(i64 i = 2; i*i <= n; ++i) {
        if(m == 1) break;
        i64 e = 0;
        while(m % i == 0) {
            ++e;
            m /= i;
        }
        if(e) res.emplace_back(i, e);
    }
    if(m > 1) res.emplace_back(m, 1);

    return res;
}

// 二分累乗
template<typename Monoid>
Monoid pow_binary(Monoid x, i64 e) {
    assert(e >= 0);

    Monoid res(1);  // 行列などの場合はここを適当に変える
    Monoid cur = x;
    while(e > 0) {
        if(e & 1)
            res *= cur;
        cur *= cur;
        e >>= 1;
    }
    return res;
}

// mod m での a の逆元
// a ⊥ m でなければならない
i64 inv_mod(i64 a, i64 m) {
    i64 g,x0; tie(g,x0,ignore) = extgcd(a, m);
    assert(g == 1);
    return modulo(x0, m);
}

template<i64 P>
struct ModPT {
    static_assert(P >= 2, "P must be a prime");
    i64 v_;  // [0,P)

    ModPT() : v_(0) {}
    ModPT(i64 v) : v_(modulo(v,P)) {}

    ModPT operator-() const {
        return ModPT(-v_);
    }
    ModPT& operator+=(ModPT rhs) {
        v_ += rhs.v_;
        v_ %= P;
        return *this;
    }
    ModPT& operator-=(ModPT rhs) {
        v_ += P;
        v_ -= rhs.v_;
        v_ %= P;
        return *this;
    }
    ModPT& operator*=(ModPT rhs) {
        v_ *= rhs.v_;
        v_ %= P;
        return *this;
    }

    ModPT inv() const {
        return ModPT(inv_mod(v_,P));
    }
};

template<i64 P>
ModPT<P> operator+(ModPT<P> lhs, ModPT<P> rhs) { return ModPT<P>(lhs) += rhs; }
template<i64 P>
ModPT<P> operator+(ModPT<P> lhs, i64 rhs) { return ModPT<P>(lhs) += rhs; }
template<i64 P>
ModPT<P> operator+(i64 lhs, ModPT<P> rhs) { return ModPT<P>(rhs) += lhs; }
template<i64 P>
ModPT<P> operator-(ModPT<P> lhs, ModPT<P> rhs) { return ModPT<P>(lhs) -= rhs; }
template<i64 P>
ModPT<P> operator-(ModPT<P> lhs, i64 rhs) { return ModPT<P>(lhs) -= rhs; }
template<i64 P>
ModPT<P> operator-(i64 lhs, ModPT<P> rhs) { return ModPT<P>(rhs) -= lhs; }
template<i64 P>
ModPT<P> operator*(ModPT<P> lhs, ModPT<P> rhs) { return ModPT<P>(lhs) *= rhs; }
template<i64 P>
ModPT<P> operator*(ModPT<P> lhs, i64 rhs) { return ModPT<P>(lhs) *= rhs; }
template<i64 P>
ModPT<P> operator*(i64 lhs, ModPT<P> rhs) { return ModPT<P>(rhs) *= lhs; }

template<i64 P>
bool operator==(ModPT<P> lhs, ModPT<P> rhs) { return lhs.v_ == rhs.v_; }
template<i64 P>
bool operator==(ModPT<P> lhs, i64 rhs) { return lhs == ModPT<P>(rhs); }
template<i64 P>
bool operator==(i64 lhs, ModPT<P> rhs) { return ModPT<P>(lhs) == rhs; }
template<i64 P>
bool operator!=(ModPT<P> lhs, ModPT<P> rhs) { return !(lhs == rhs); }
template<i64 P>
bool operator!=(ModPT<P> lhs, i64 rhs) { return !(lhs == rhs); }
template<i64 P>
bool operator!=(i64 lhs, ModPT<P> rhs) { return !(lhs == rhs); }

template<i64 P>
istream& operator>>(istream& in, ModPT<P>& x) {
    return in >> x.v_;
}

template<i64 P>
ostream& operator<<(ostream& out, ModPT<P> x) {
    return out << x.v_;
}

using ModP = ModPT<MOD>;

// F(0) = 0
// F(1) = 1
// F(n) = F(n-1) + F(n-2)
//
// // decltype(auto) で受けると SIZE() が使える (auto だとポインタになってしまう)
// decltype(auto) fib = fibonacci<1000>();
template<size_t N>
ModP (&fibonacci())[N] {
    static_assert(N >= 2, "");
    static ModP fib[N];

    fib[0] = 0;
    fib[1] = 1;
    FOR(i, 2, N) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    return fib;
}

// }}}
