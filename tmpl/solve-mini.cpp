/**
 * 
 */

// header {{{
#include <bits/stdc++.h>
using namespace std;

#define CPP_STR(x) CPP_STR_I(x)
#define CPP_CAT(x,y) CPP_CAT_I(x,y)
#define CPP_STR_I(args...) #args
#define CPP_CAT_I(x,y) x ## y

#define SFINAE(pred...) std::enable_if_t<(pred), std::nullptr_t> = nullptr

#define ASSERT(expr...) assert((expr))

using i8  = int8_t;
using u8  = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;
using f80 = __float80;
// }}}

constexpr i64 INF  = INT64_C(1'010'000'000'000'000'017);
constexpr f64 FINF = 1e100;

constexpr i64 MOD = INT64_C(1'000'000'007);

constexpr f64 EPS = 1e-12;

constexpr f64 PI = 3.14159265358979323846;

// util {{{
#define FOR(i, start, end) for(i64 i = (start), CPP_CAT(i,xxxx_end)=(end); i < CPP_CAT(i,xxxx_end); ++i)
#define REP(i, n) FOR(i, 0, n)

#define ALL(f,c,...) (([&](decltype((c)) cccc) { return (f)(std::begin(cccc), std::end(cccc), ## __VA_ARGS__); })(c))

template<typename C>
constexpr i64 SIZE(const C& c) noexcept { return static_cast<i64>(c.size()); }

template<typename T, size_t N>
constexpr i64 SIZE(const T (&)[N]) noexcept { return static_cast<i64>(N); }

template<typename T, typename U, typename Comp=less<>>
constexpr bool chmax(T& xmax, const U& x, Comp comp={}) noexcept {
    if(comp(xmax, x)) {
        xmax = x;
        return true;
    }
    return false;
}

template<typename T, typename U, typename Comp=less<>>
constexpr bool chmin(T& xmin, const U& x, Comp comp={}) noexcept {
    if(comp(x, xmin)) {
        xmin = x;
        return true;
    }
    return false;
}

// tuple {{{
template<i64 I=0, typename F, typename... TS, SFINAE(sizeof...(TS) == I)>
void tuple_enumerate(tuple<TS...>&, F&&) {}

template<i64 I=0, typename F, typename... TS, SFINAE(sizeof...(TS) > I)>
void tuple_enumerate(tuple<TS...>& t, F&& f) {
    f(I, get<I>(t));
    tuple_enumerate<I+1>(t, forward<F>(f));
}

template<i64 I=0, typename F, typename... TS, SFINAE(sizeof...(TS) == I)>
void tuple_enumerate(const tuple<TS...>&, F&&) {}

template<i64 I=0, typename F, typename... TS, SFINAE(sizeof...(TS) > I)>
void tuple_enumerate(const tuple<TS...>& t, F&& f) {
    f(I, get<I>(t));
    tuple_enumerate<I+1>(t, forward<F>(f));
}
// }}}

// container {{{
template<typename T> struct is_container : false_type {};
template<typename T, size_t N> struct is_container<array<T,N>> : true_type {};
template<typename... Args> struct is_container<vector<Args...>> : true_type {};
template<typename... Args> struct is_container<deque<Args...>> : true_type {};
template<typename... Args> struct is_container<list<Args...>> : true_type {};
template<typename... Args> struct is_container<forward_list<Args...>> : true_type {};
template<typename... Args> struct is_container<set<Args...>> : true_type {};
template<typename... Args> struct is_container<multiset<Args...>> : true_type {};
template<typename... Args> struct is_container<unordered_set<Args...>> : true_type {};
template<typename... Args> struct is_container<unordered_multiset<Args...>> : true_type {};
template<typename... Args> struct is_container<map<Args...>> : true_type {};
template<typename... Args> struct is_container<multimap<Args...>> : true_type {};
template<typename... Args> struct is_container<unordered_map<Args...>> : true_type {};
template<typename... Args> struct is_container<unordered_multimap<Args...>> : true_type {};

template<typename T, typename Hash=hash<T>, typename Eq=equal_to<T>>
using HashSet = unordered_set<T,Hash,Eq>;
template<typename K, typename V, typename Hash=hash<K>, typename Eq=equal_to<K>>
using HashMap = unordered_map<K,V,Hash,Eq>;
template<typename T, typename Hash=hash<T>, typename Eq=equal_to<T>>
using HashMultiset = unordered_multiset<T,Hash,Eq>;
template<typename K, typename V, typename Hash=hash<K>, typename Eq=equal_to<K>>
using HashMultimap = unordered_multimap<K,V,Hash,Eq>;

template<typename T>
using MaxHeap = priority_queue<T, vector<T>, less<T>>;
template<typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

template<typename T>
auto vec_make(i64 n, T x) {
    return vector<T>(n, x);
}

template<typename T, typename... Args, SFINAE(sizeof...(Args) >= 2)>
auto vec_make(i64 n, Args... args) {
    auto inner = vec_make<T>(args...);
    return vector<decltype(inner)>(n, inner);
}

template<typename T, size_t N, size_t... NS>
struct ArrayType {
    using type = array<typename ArrayType<T,NS...>::type,N>;
};

template<typename T, size_t N>
struct ArrayType<T,N> {
    using type = array<T,N>;
};

template<typename T, size_t... NS>
using Array = typename ArrayType<T,NS...>::type;

template<typename T, size_t N>
T& array_at(Array<T,N>& ary, i64 i) {
    return ary[i];
}

template<typename T, size_t N, size_t... NS, typename... Args>
T& array_at(Array<T,N,NS...>& ary, i64 i, Args... args) {
    return array_at<T,NS...>(ary[i], args...);
}

template<typename T, size_t N>
const T& array_at(const Array<T,N>& ary, i64 i) {
    return ary[i];
}

template<typename T, size_t N, size_t... NS, typename... Args>
const T& array_at(const Array<T,N,NS...>& ary, i64 i, Args... args) {
    return array_at<T,NS...>(ary[i], args...);
}

template<typename T>
auto reserve_vec(i64 cap) {
    vector<T> res;
    res.reserve(cap);
    return res;
}

template<typename T, typename Hash=hash<T>, typename Eq=equal_to<T>>
auto reserve_hash_set(i64 cap, f32 load_max=0.25) {
    HashSet<T,Hash,Eq> res;
    res.max_load_factor(load_max);
    res.reserve(cap);
    return res;
}

template<typename K, typename V, typename Hash=hash<K>, typename Eq=equal_to<K>>
auto reserve_hash_map(i64 cap, f32 load_max=0.25) {
    HashMap<K,V,Hash,Eq> res;
    res.max_load_factor(load_max);
    res.reserve(cap);
    return res;
}

template<typename T, typename Hash=hash<T>, typename Eq=equal_to<T>>
auto reserve_hash_multiset(i64 cap, f32 load_max=0.25) {
    HashMultiset<T,Hash,Eq> res;
    res.max_load_factor(load_max);
    res.reserve(cap);
    return res;
}

template<typename K, typename V, typename Hash=hash<K>, typename Eq=equal_to<K>>
auto reserve_hash_multimap(i64 cap, f32 load_max=0.25) {
    HashMultimap<K,V,Hash,Eq> res;
    res.max_load_factor(load_max);
    res.reserve(cap);
    return res;
}

template<typename T, typename C>
T POP(stack<T,C>& stk) {
    T x = stk.top(); stk.pop();
    return x;
}

template<typename T, typename C>
T POP(queue<T,C>& que) {
    T x = que.front(); que.pop();
    return x;
}

template<typename T, typename C, typename Comp>
T POP(priority_queue<T,C,Comp>& que) {
    T x = que.top(); que.pop();
    return x;
}
// }}}

// fixpoint {{{
template<typename F>
class FixPoint {
public:
    explicit constexpr FixPoint(F&& f) : f_(forward<F>(f)) {}

    template<typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const {
        return f_(*this, forward<Args>(args)...);
    }

private:
    F f_;
};

template<typename F>
constexpr decltype(auto) FIX(F&& f) {
    return FixPoint<F>(forward<F>(f));
}

template<typename F, size_t... NS>
class FixPointMemo {
public:
    explicit FixPointMemo(F&& f) : f_(forward<F>(f)) {}

    template<typename... Args>
    decltype(auto) operator()(Args... args) const {
        using R = decltype(f_(*this,args...));
        static Array<bool,NS...> done {};
        static Array<R,NS...>    memo;

        if(!array_at<bool,NS...>(done,args...)) {
            array_at<R,NS...>(memo,args...) = f_(*this,args...);
            array_at<bool,NS...>(done,args...) = true;
        }
        return array_at<R,NS...>(memo,args...);
    }

private:
    F f_;
};

template<size_t... NS, typename F>
decltype(auto) FIXMEMO(F&& f) {
    return FixPointMemo<F,NS...>(forward<F>(f));
}
// }}}

// input {{{
template<typename T, typename Enable=void>
struct Scan {
    static T scan(istream& in) {
        T res;
        in >> res;
        return res;
    }
};

template<typename T, typename Enable=void>
struct Scan1;

template<typename T>
struct Scan1<T,enable_if_t<is_integral<T>::value && !is_same<T,bool>::value>> {
    static T scan1(istream& in) {
        return Scan<T>::scan(in) - 1;
    }
};

template<typename T=i64>
T RD() {
    return Scan<T>::scan(cin);
}

template<typename T=i64>
T RD1() {
    return Scan1<T>::scan1(cin);
}

template<typename T=i64>
auto RD_VEC(i64 n) {
    auto res = reserve_vec<T>(n);
    REP(_, n) {
        res.emplace_back(RD<T>());
    }
    return res;
}

template<typename T=i64>
auto RD1_VEC(i64 n) {
    auto res = reserve_vec<T>(n);
    REP(_, n) {
        res.emplace_back(RD1<T>());
    }
    return res;
}
// }}}

// output {{{
template<typename T, typename Enable=void>
struct Fmt {
    static void fmt(ostream& out, const T& x) { out << x; }
};

template<typename T>
void fmt_write(ostream& out, const T& x) {
    Fmt<T>::fmt(out, x);
}

template<typename... TS>
struct Fmt<tuple<TS...>> {
    static void fmt(ostream& out, const tuple<TS...>& t) {
        tuple_enumerate(t, [&out](i64 i, const auto& e) {
            if(i != 0) out << ' ';
            fmt_write(out, e);
        });
    }
};

template<typename T1, typename T2>
struct Fmt<pair<T1,T2>> {
    static void fmt(ostream& out, const pair<T1,T2>& p) {
        return fmt_write(out, make_tuple(p.first,p.second));
    }
};

template<typename C>
struct Fmt<C,enable_if_t<is_container<C>::value>> {
    static void fmt(ostream& out, const C& c) {
        for(auto it = begin(c); it != end(c); ++it) {
            if(it != begin(c)) out << ' ';
            fmt_write(out, *it);
        }
    }
};

void PRINT() {}

template<typename T, typename... TS>
void PRINT(const T& x, const TS&... args) {
    fmt_write(cout, x);
    if(sizeof...(args) > 0) {
        cout << ' ';
        PRINT(args...);
    }
}

template<typename... TS>
void PRINTLN(const TS&... args) {
    PRINT(args...);
    cout << '\n';
}
// }}}

// debug {{{
template<typename T, typename Enable=void>
struct Dbg {
    static void dbg(ostream& out, const T& x) { out << x; }
};

template<typename T>
void dbg_write(ostream& out, const T& x) {
    return Dbg<T>::dbg(out, x);
}

template<>
struct Dbg<i64> {
    static void dbg(ostream& out, i64 x) {
        if(x == INF)
            out << "INF";
        else if(x == -INF)
            out << "-INF";
        else
            out << x;
    }
};

template<>
struct Dbg<f64> {
    static void dbg(ostream& out, f64 x) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
        if(x == FINF)
            out << "FINF";
        else if(x == -FINF)
            out << "-FINF";
        else
            out << x;
#pragma GCC diagnostic pop
    }
};

template<typename T, size_t N>
struct Dbg<T[N]> {
    static void dbg(ostream& out, const T (&ary)[N]) {
        out << "[";
        REP(i, N) {
            if(i != 0) out << ",";
            dbg_write(out, ary[i]);
        }
        out << "]";
    }
};

template<typename... TS>
struct Dbg<tuple<TS...>> {
    static void dbg(ostream& out, const tuple<TS...>& t) {
        out << "(";
        tuple_enumerate(t, [&out](i64 i, const auto& e) {
            if(i != 0) out << ",";
            dbg_write(out, e);
        });
        out << ")";
    }
};

template<typename T1, typename T2>
struct Dbg<pair<T1,T2>> {
    static void dbg(ostream& out, const pair<T1,T2>& p) {
        return dbg_write(out, make_tuple(p.first,p.second));
    }
};

template<typename C>
struct Dbg<C,enable_if_t<is_container<C>::value>> {
    static void dbg(ostream& out, const C& c) {
        out << "[";
        for(auto it = begin(c); it != end(c); ++it) {
            if(it != begin(c)) out << ",";
            dbg_write(out, *it);
        }
        out << "]";
    }
};

template<typename T>
void DBG_IMPL(i64 line, const char* expr, const T& value) {
    cerr << "[L " << line << "]: ";
    cerr << expr << " = ";
    dbg_write(cerr, value);
    cerr << "\n";
}

template<typename... TS>
void DBG_IMPL(i64 line, const char* expr, const TS&... value) {
    cerr << "[L " << line << "]: ";
    cerr << "(" << expr << ") = ";
    dbg_write(cerr, make_tuple(value...));
    cerr << "\n";
}

template<size_t N, typename T, SFINAE(rank<T>::value == 0)>
void DBG_DP_IMPL_HELPER(ostream& out, const T& x, const array<i64,N>&, const array<i64,N>&) {
    dbg_write(out, x);
}

template<size_t N, typename T, SFINAE(rank<T>::value > 0)>
void DBG_DP_IMPL_HELPER(ostream& out, const T& x, const array<i64,N>& sizes, const array<i64,N>& offs) {
    i64 k   = N - rank<T>::value;
    i64 off = offs[k];
    i64 siz = sizes[k];
    if(siz == 0) siz = extent<T>::value - off;

    out << "[";
    FOR(i, off, off+siz) {
        if(i != off) out << ",";
        DBG_DP_IMPL_HELPER(out, x[i], sizes, offs);
    }
    out << "]";
}

template<typename T, SFINAE(rank<T>::value > 0)>
void DBG_DP_IMPL(i64 line, const char* expr, const T& dp,
                 const array<i64,rank<T>::value>& sizes={},
                 const array<i64,rank<T>::value>& offs={})
{
    cerr << "[L " << line << "]: ";
    cerr << expr << " = ";
    DBG_DP_IMPL_HELPER<rank<T>::value>(cerr, dp, sizes, offs);
    cerr << "\n";
}

#ifdef PROCON_LOCAL
    #define DBG(args...) DBG_IMPL(__LINE__, CPP_STR_I(args), args)
    #define DBG_DP(args...) DBG_DP_IMPL(__LINE__, CPP_STR_I(args), args)
#else
    #define DBG(args...)
    #define DBG_DP(args...)
#endif
// }}}

// modint {{{
template<i64 P>
struct ModPT {
    static_assert(P >= 2, "P must be a prime");
    i64 v_;  // [0,P)

    ModPT() : v_(0) {}
    ModPT(i64 v) {
        i64 r = v % P;
        v_ = r >= 0 ? r : r+P;
    }

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
        return exchange(*this, *this+1);
    }
    ModPT operator--(int) {
        return exchange(*this, *this-1);
    }

    explicit operator i64() const { return v_; }
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
struct Scan<ModPT<P>> {
    static ModPT<P> scan(istream& in) {
        return Scan<i64>::scan(in);
    }
};

template<i64 P>
struct Fmt<ModPT<P>> {
    static void fmt(ostream& out, ModPT<P> x) {
        fmt_write(out, x.v_);
    }
};

template<i64 P>
struct Dbg<ModPT<P>> {
    static void dbg(ostream& out, ModPT<P> x) {
        dbg_write(out, x.v_);
    }
};

using ModP = ModPT<MOD>;
// }}}
// }}}

// init {{{
struct ProconInit {
    static constexpr int IOS_PREC = 15;
    static constexpr bool AUTOFLUSH = false;

    ProconInit() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(IOS_PREC);
#ifdef PROCON_LOCAL
        cin.exceptions(ios::failbit | ios::badbit);
        cerr << fixed << setprecision(IOS_PREC);
#endif
        if(AUTOFLUSH)
            cout << unitbuf;
    }
} PROCON_INIT;
// }}}

//--------------------------------------------------------------------

void solve() {
    

    //PRINTLN(ans);
}

signed main() {
    

    solve();

    return 0;
}
