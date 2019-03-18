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
    return { g, x, y };
}

// 素因数分解
// (素因数,指数) のリストを返す
vector<pair<i64,i64>> factorize(i64 n) {
    assert(n >= 2);

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

// }}}
