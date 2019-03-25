// num {{{

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

    ModPT& operator++() {
        return *this += 1;
    }
    ModPT& operator--() {
        return *this -= 1;
    }
    ModPT operator++(int) {
        ModPT res(*this);
        ++*this;
        return res;
    }
    ModPT operator--(int) {
        ModPT res(*this);
        --*this;
        return res;
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
struct Formatter<ModPT<P>> {
    static ostream& write_str(ostream& out, ModPT<P> x) {
        return WRITE_STR(out, x.v_);
    }
    static ostream& write_repr(ostream& out, ModPT<P> x) {
        return WRITE_REPR(out, x.v_);
    }
};

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
    static ModP fib[N] {};

    if(fib[1] != 1) {
        fib[0] = 0;
        fib[1] = 1;
        FOR(i, 2, N) {
            fib[i] = fib[i-1] + fib[i-2];
        }
    }
    return fib;
}

template<size_t N>
ModP (&factorial())[N] {
    static_assert(N >= 1, "");
    static ModP fac[N] {};

    if(fac[0] != 1) {
        fac[0] = 1;
        FOR(i, 1, N) {
            fac[i] = i * fac[i-1];
        }
    }
    return fac;
}

template<size_t N>
ModP (&ifactorial())[N] {
    static_assert(N >= 1, "");
    static ModP ifac[N] {};

    if(ifac[0] != 1) {
        decltype(auto) fac = factorial<N>();
        ifac[N-1] = fac[N-1].inv();
        for(i64 i = N-2; i >= 0; --i) {
            ifac[i] = (i+1) * ifac[i+1];
        }
    }
    return ifac;
}

ModP permutation_count(i64 n, i64 r, const ModP* fac, const ModP* ifac) {
    if(n < r) return 0;
    return fac[n] * ifac[n-r];
}

ModP combination_count(i64 n, i64 r, const ModP* fac, const ModP* ifac) {
    if(n < r) return 0;
    return fac[n] * ifac[r] * ifac[n-r];
}

// 分割数 P(n,k) (n を k 個の正整数の和で表す場合の数)
//
// 「n を 最大値 k の正整数の和で表す場合の数」でもある。
// 「n を k 個『以下』の正整数の和で表す場合の数」は sum(P(n,i)) (1<=i<=k)
// 「n を k 個の『非負整数』の和で表す場合の数」は P(n+k,k)
//
// P(0,0) = 1
// P(n,0) = 0
// P(0,k) = 0
// n < k のとき P(n,k) = 0
// P(n,1) = 1
// P(n,n) = 1
template<size_t H, size_t W>
ModP (&partition_count())[H][W] {
    static_assert(W >= 1 && H >= W, "");
    static ModP dp[H][W] {};

    if(dp[0][0] != 1) {
        REP(j, W) {
            dp[j][j] = 1;
        }
        FOR(i, 2, H) {
            dp[i][1] = 1;
        }
        FOR(i, 3, H) {
            FOR(j, 2, min<i64>(i,W)) {
                dp[i][j] = dp[i-1][j-1] + dp[i-j][j];
            }
        }
    }
    return dp;
}

// 分割数 メモ化再帰版
template<size_t H, size_t W>
auto partition_count_func() {
    static_assert(W >= 1 && H >= W, "");
    auto f = FIX([](auto self, i64 n, i64 k) -> ModP {
        static bool done[H][W] {};
        static ModP memo[H][W];

        if(n <  k) return 0;
        if(n == k) return 1;
        if(k == 1) return 1;

        if(!done[n][k]) {
            ModP res = self(n-1,k-1) + self(n-k,k);

            memo[n][k] = res;
            done[n][k] = true;
        }
        return memo[n][k];
    });
    return f;
}

// }}}
