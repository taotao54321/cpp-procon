// {{{ header
#include <bits/stdc++.h>
using namespace std;

using i8   = int8_t;
using u8   = uint8_t;
using i16  = int16_t;
using u16  = uint16_t;
using i32  = int32_t;
using u32  = uint32_t;
using i64  = int64_t;
using u64  = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

using f32  = float;
using f64  = double;
using f80  = __float80;
using f128 = __float128;
// }}}

constexpr i64 INF = 1'010'000'000'000'000'000LL;

constexpr i64 MOD = 1'000'000'007LL;

constexpr f64 EPS = 1e-12;

constexpr f64 PI = 3.14159265358979323846;

// {{{ util
#define FOR(i, start, end) for(i64 i = (start), i##_end=(end); i < i##_end; ++i)
#define REP(i, n) FOR(i, 0, n)

#define ALL(f,c,...) (([&](decltype((c)) cccc) { return (f)(begin(cccc), end(cccc), ## __VA_ARGS__); })(c))
#define SLICE(f,c,l,r,...) (([&](decltype((c)) cccc, decltype((l)) llll, decltype((r)) rrrr) {\
    auto iiii = llll <= rrrr ? begin(cccc)+llll : end(cccc);\
    auto jjjj = llll <= rrrr ? begin(cccc)+rrrr : end(cccc);\
    return (f)(iiii, jjjj, ## __VA_ARGS__);\
})(c,l,r))

bool is_odd (i64 x) { return x % 2 != 0; }
bool is_even(i64 x) { return x % 2 == 0; }

template<typename T> i64 cmp(T x, T y) { return (y<x) - (x<y); }
template<typename T> i64 sgn(T x) { return cmp(x, T(0)); }

template<typename T, typename U>
bool chmax(T& xmax, const U& x) {
    if(xmax < x) {
        xmax = x;
        return true;
    }
    else {
        return false;
    }
}

template<typename T, typename U>
bool chmin(T& xmin, const U& x) {
    if(x < xmin) {
        xmin = x;
        return true;
    }
    else {
        return false;
    }
}

template<typename T>
void RD(T& x) {
    cin >> x;
#ifdef PROCON_LOCAL
    assert(cin);
#endif
}

template<typename T>
void RD(vector<T>& v, i64 n) {
    v.reserve(n);
    REP(_, n) {
        T e; RD(e);
        v.emplace_back(e);
    }
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for(auto first = begin(v), it = first; it != end(v); ++it) {
        if(it != first)
            out << ' ';
        out << *it;
    }
    return out;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1,T2>& p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

void PRINT() {}

template<typename T, typename... TS>
void PRINT(const T& x, const TS& ...args) {
    cout << x;
    if(sizeof...(args)) {
        cout << ' ';
        PRINT(args...);
    }
}

template<typename... TS>
void PRINTLN(const TS& ...args) {
    PRINT(args...);
    cout << '\n';
}

template<typename T>
void DBG_IMPL(i64 line, const char* expr, const T& value) {
#ifdef PROCON_LOCAL
    cerr << "[LINE " << line << "]: ";
    cerr << expr << " = " << value << "\n";
#endif
}

#define DBG(expr) DBG_IMPL(__LINE__, #expr, (expr))
// }}}

// {{{ init
struct ProconInit {
    static constexpr int IOS_PREC = 15;
    static constexpr bool AUTOFLUSH = false;

    ProconInit() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(IOS_PREC);
#ifdef PROCON_LOCAL
        cerr << fixed << setprecision(IOS_PREC);
#endif
        if(AUTOFLUSH)
            cout << unitbuf;
    }
};
// }}}
