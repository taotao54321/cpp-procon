// num {{{

vector<Int> divisors_proper(Int n) {
    if(n == 1) return {};
    vector<Int> res(1, 1);

    Int d = 2;
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

vector<Int> divisors(Int n) {
    vector<Int> res = divisors_proper(n);
    res.emplace_back(n);
    return res;
}

// 素因数分解
// (素因数,指数) のリストを返す
// n >= 1 でなければならない
// n == 1 の場合、空リストを返す
vector<pair<Int,Int>> factorize(Int n) {
    ASSERT(n >= 1);

    vector<pair<Int,Int>> res;

    for(Int p = 2; p*p <= n; ++p) {
        Int e = 0;
        while(n % p == 0) {
            ++e;
            n /= p;
        }
        if(e) res.emplace_back(p, e);
    }
    if(n > 1) res.emplace_back(n, 1);

    return res;
}

bool is_square(Int x) {
    Int r = sqrt_floor(x);
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

bool is_prime(Int n) {
    ASSERT(n >= 0);
    if(is_same<Int,i64>::value)
        return is_prime_u64(u64(n));
    else if(is_same<Int,i32>::value)
        return is_prime_u32(u32(n));
    ASSERT(false);
}

// エラトステネスのふるい
template<Int N>
bool (&is_prime_table())[N] {
    static_assert(N >= 3, "");
    static bool prime[N] {};

    if(!prime[2]) {
        fill(begin(prime)+2, end(prime), true);
        for(Int i = 2; i*i <= N-1; ++i) {
            if(!prime[i]) continue;
            for(Int j = i+i; j < N; j += i)
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
template<Int N>
ModInt (&fibonacci_table())[N] {
    static_assert(N >= 2, "");
    static ModInt fib[N] {};

    if(fib[1] != 1) {
        fib[0] = 0;
        fib[1] = 1;
        FOR(i, 2, N) {
            fib[i] = fib[i-1] + fib[i-2];
        }
    }
    return fib;
}

template<Int N>
struct Factorial {
    static_assert(N >= 1, "");

    static ModInt fac(Int n) {
        static decltype(auto) table = fac_table();
        return table[n];
    }

    static ModInt ifac(Int n) {
        static decltype(auto) table = ifac_table();
        return table[n];
    }

    static ModInt perm(Int n, Int r) {
        if(n < 0 || r < 0 || n < r) return 0;
        return fac(n) * ifac(n-r);
    }

    static ModInt comb(Int n, Int r) {
        if(n < 0 || r < 0 || n < r) return 0;
        return fac(n) * ifac(n-r) * ifac(r);
    }

    // O(r)
    // n が大きい場合に使う
    static ModInt comb_linear(Int n, Int r) {
        ModInt res = 1;
        REP(i, r) {
            res *= n-i;
        }
        res *= ifac(r);
        return res;
    }

    // nHr
    static ModInt repcomb(Int n, Int r) {
        if(n < 0 || r < 0) return 0;
        if(n == 0 && r == 0) return 1;
        return comb(n+r-1, r);
    }

private:
    static const ModInt (&fac_table())[N] {
        static ModInt table[N] {};
        ASSERT(table[0] == 0);  // CALL ONLY ONCE
        table[0] = 1;
        FOR(i, 1, N) {
            table[i] = i * table[i-1];
        }
        return table;
    }

    static const ModInt (&ifac_table())[N] {
        static ModInt table[N] {};
        ASSERT(table[0] == 0);  // CALL ONLY ONCE
        table[N-1] = fac(N-1).inv();
        for(Int i = N-2; i >= 0; --i) {
            table[i] = (i+1) * table[i+1];
        }
        return table;
    }
};

template<Int H, Int W>
ModInt (&combination_count_table())[H][W] {
    static_assert(W >= 1 && H >= W, "");
    static ModInt dp[H][W] {};

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

template<Int H, Int W>
auto combination_count_func() {
    static_assert(W >= 1 && H >= W, "");
    return FIXMEMO<H,W>([](auto&& self, Int n, Int r) -> ModInt {
        if(n <  r) return 0;
        if(r == 0) return 1;
        if(n == r) return 1;
        return self(n-1,r-1) + self(n-1,r);
    });
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
//
// 順序を区別するものは合成(composition)とよばれる。
// 「n を k 個の順序つき正整数列の和で表す場合の数」は Q(n,k) = comb(n-1,k-1)
// 「n を k 個の順序つき『非負整数』列の和で表す場合の数」は Q(n+k,k) = comb(n+k-1,k-1) = comb(n+k-1,n)
// 「n を順序つき正整数列の和で表す場合の数」は 2^(n-1)
template<Int H, Int W>
ModInt (&partition_count_table())[H][W] {
    static_assert(W >= 1 && H >= W, "");
    static ModInt dp[H][W] {};

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
template<Int H, Int W>
auto partition_count_func() {
    static_assert(W >= 1 && H >= W, "");
    return FIXMEMO<H,W>([](auto&& self, Int n, Int k) -> ModInt {
        if(n <  k) return 0;
        if(n == k) return 1;
        if(k == 1) return 1;
        return self(n-1,k-1) + self(n-k,k);
    });
}

// }}}
