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


