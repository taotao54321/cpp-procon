// num {{{

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
    i64 g = extgcd_impl(ABS(a), ABS(b), x, y);
    x *= sgn(a);
    y *= sgn(b);
    return make_tuple(g, x, y);
}

vector<i64> divisors_proper(i64 n) {
    if(n == 1) return {};
    vector<i64> res(1, 1);

    i64 d = 2;
    for(; d*d < n; ++d) {
        if(n % d == 0) {
            res.emplace_back(d);
            res.emplace_back(n/d);
        }
    }
    if(d*d == n)
        res.emplace_back(d);

    return res;
}

vector<i64> divisors(i64 n) {
    vector<i64> res = divisors_proper(n);
    res.emplace_back(n);
    return res;
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

bool is_square(i64 x) {
    i64 r = sqrt_floor(x);
    return r*r == x;
}

// Miller-Rabin 法
//
// 参考: http://miller-rabin.appspot.com/
bool is_prime_u32(u32 n) {
    static constexpr u32 AS[] {
         2,
         7,
        61,
    };

    static const auto mulmod32 = [](u32 a, u32 b, u32 m) -> u32 {
        u64 res = a;
        res *= b;
        res %= m;
        return static_cast<u32>(res);
    };

    static const auto powmod32 = [](u32 a, u32 b, u32 m) -> u32 {
        u32 res = 1;
        while(b > 0) {
            if(b & 1)
                res = mulmod32(res, a, m);
            a = mulmod32(a, a, m);
            b >>= 1;
        }
        return res;
    };

    if(n <= 1)     return false;
    if(n == 2)     return true;
    if(n % 2 == 0) return false;

    u32 d = n-1;
    u32 s = __builtin_ctz(d);
    d >>= s;

    for(u32 a : AS) {
        if(a >= n) a %= n;
        if(a == 0) continue;

        u32 x = powmod32(a, d, n);
        if(x == 1 || x == n-1) continue;

        u32 r;
        for(r = 1; r < s; ++r) {
            x = mulmod32(x, x, n);
            if(x == 1)   return false;
            if(x == n-1) break;
        }
        if(r == s) return false;
    }

    return true;
}

bool is_prime_u64(u64 n) {
    static constexpr u64 AS[] {
                 2,
               325,
              9375,
             28178,
            450775,
           9780504,
        1795265022,
    };

    static const auto mulmod64 = [](u64 a, u64 b, u64 m) -> u64 {
        u128 res = a;
        res *= b;
        res %= m;
        return static_cast<u64>(res);
    };

    static const auto powmod64 = [](u64 a, u64 b, u64 m) -> u64 {
        u64 res = 1;
        while(b > 0) {
            if(b & 1)
                res = mulmod64(res, a, m);
            a = mulmod64(a, a, m);
            b >>= 1;
        }
        return res;
    };

    if(n <= numeric_limits<u32>::max()) return is_prime_u32(static_cast<u32>(n));
    if(n % 2 == 0) return false;

    u64 d = n-1;
    u64 s = __builtin_ctzll(d);
    d >>= s;

    for(u64 a : AS) {
        if(a >= n) a %= n;
        if(a == 0) continue;

        u64 x = powmod64(a, d, n);
        if(x == 1 || x == n-1) continue;

        u64 r;
        for(r = 1; r < s; ++r) {
            x = mulmod64(x, x, n);
            if(x == 1)   return false;
            if(x == n-1) break;
        }
        if(r == s) return false;
    }

    return true;
}

bool is_prime(i64 n) {
    assert(n >= 0);
    return is_prime_u64(static_cast<u64>(n));
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

    explicit operator i64() const { return v_; }

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
    i64 t; in >> t;
    x = t;
    return in;
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

// エラトステネスのふるい
template<i64 N>
bool (&is_prime_table())[N] {
    static_assert(N >= 3, "");
    static bool prime[N] {};

    if(!prime[2]) {
        fill(begin(prime)+2, end(prime), true);
        for(i64 i = 2; i*i <= N-1; ++i) {
            if(!prime[i]) continue;
            for(i64 j = i+i; j < N; j += i)
                prime[j] = false;
        }
    }
    return prime;
}

// F(0) = 0
// F(1) = 1
// F(n) = F(n-1) + F(n-2)
//
// // decltype(auto) で受けると SIZE() が使える (auto だとポインタになってしまう)
// decltype(auto) fib = fibonacci_table<1000>();
template<i64 N>
ModP (&fibonacci_table())[N] {
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

template<i64 N>
ModP (&factorial_table())[N] {
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

template<i64 N>
ModP (&ifactorial_table())[N] {
    static_assert(N >= 1, "");
    static ModP ifac[N] {};

    if(ifac[0] != 1) {
        decltype(auto) fac = factorial_table<N>();
        ifac[N-1] = fac[N-1].inv();
        for(i64 i = N-2; i >= 0; --i) {
            ifac[i] = (i+1) * ifac[i+1];
        }
    }
    return ifac;
}

ModP permutation_count_fac(i64 n, i64 r, const ModP* fac, const ModP* ifac) {
    if(n < r) return 0;
    return fac[n] * ifac[n-r];
}

template<i64 H, i64 W>
ModP (&combination_count_table())[H][W] {
    static_assert(W >= 1 && H >= W, "");
    static ModP dp[H][W] {};

    if(dp[0][0] != 1) {
        REP(i, H) {
            dp[i][0] = 1;
            dp[i][i] = 1;
        }
        FOR(i, 1, H) FOR(j, 1, i) {
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        }
    }
    return dp;
}

template<i64 H, i64 W>
auto combination_count_func() {
    static_assert(W >= 1 && H >= W, "");
    return MEMOIZE<H,W>([](auto&& self, i64 n, i64 r) -> ModP {
        if(n <  r) return 0;
        if(r == 0) return 1;
        if(n == r) return 1;
        return self(n-1,r-1) + self(n-1,r);
    });
}

ModP combination_count_fac(i64 n, i64 r, const ModP* fac, const ModP* ifac) {
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
template<i64 H, i64 W>
ModP (&partition_count_table())[H][W] {
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
            FOR(j, 2, MIN(i,W)) {
                dp[i][j] = dp[i-1][j-1] + dp[i-j][j];
            }
        }
    }
    return dp;
}

// 分割数 メモ化再帰版
template<i64 H, i64 W>
auto partition_count_func() {
    static_assert(W >= 1 && H >= W, "");
    return MEMOIZE<H,W>([](auto&& self, i64 n, i64 k) -> ModP {
        if(n <  k) return 0;
        if(n == k) return 1;
        if(k == 1) return 1;
        return self(n-1,k-1) + self(n-k,k);
    });
}

// }}}
