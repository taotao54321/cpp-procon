// fft {{{

complex64 root_of_unity(i64 n, i64 k) {
    return polar(1.0, 2*PI*f64(k) / f64(n));
}

// SIZE(a) は2ベキであること
vector<complex64> dft(const vector<complex64>& a) {
    i64 n = SIZE(a);
    if(n == 1) return a;

    vector<complex64> a0(n/2);
    vector<complex64> a1(n/2);
    REP(i, n/2) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }

    vector<complex64> inv_a0 = dft(a0);
    vector<complex64> inv_a1 = dft(a1);

    vector<complex64> inv_a(n);
    REP(i, n) {
        i64 j = i & (n/2-1);
        complex64 z = root_of_unity(n, i);
        inv_a[i] = inv_a0[j] + z*inv_a1[j];
    }
    return inv_a;
}

// SIZE(a) は2ベキであること
vector<complex64> idft(const vector<complex64>& inv_a) {
    i64 n = SIZE(inv_a);

    vector<complex64> a = dft(inv_a);
    reverse(begin(a)+1, end(a));
    ALL(for_each, a, [n](auto& e) { e /= f64(n); });

    return a;
}

vector<complex64> convolute(vector<complex64>& a, vector<complex64>& b) {
    i64 n = pow2_ceil(SIZE(a) + SIZE(b) - 1);
    a.resize(n);
    b.resize(n);

    vector<complex64> inv_a = dft(a);
    vector<complex64> inv_b = dft(b);

    vector<complex64> inv_c(n);
    REP(i, n) {
        inv_c[i] = inv_a[i] * inv_b[i];
    }

    return idft(inv_c);
}

// }}}
