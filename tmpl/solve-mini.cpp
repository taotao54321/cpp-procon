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
//constexpr i64 MOD = INT64_C(998'244'353);

constexpr f64 EPS = 1e-12;

constexpr f64 PI = 3.14159265358979323846;

// util {{{
#define FOR(i, start, end) for(i64 i = (start), CPP_CAT(i,xxxx_end)=(end); i < CPP_CAT(i,xxxx_end); ++i)
#define REP(i, n) FOR(i, 0, n)

#define ALL(f,c,...) (([&](decltype((c)) cccc) { return (f)(std::begin(cccc), std::end(cccc), ## __VA_ARGS__); })(c))

#define LIFT(f) ([](auto&&... args) -> decltype(auto) { return (f)(std::forward<decltype(args)>(args)...); })

template<typename C>
constexpr i64 SIZE(const C& c) noexcept { return static_cast<i64>(c.size()); }

template<typename T, size_t N>
constexpr i64 SIZE(const T (&)[N]) noexcept { return static_cast<i64>(N); }

template<typename T, SFINAE(is_signed<T>::value)>
constexpr T ABS(T x) noexcept {
    return x < 0 ? -x : x;
}

template<typename T>
constexpr i64 CMP(T x, T y) noexcept { return (y<x) - (x<y); }

template<typename T>
constexpr i64 SGN(T x) noexcept { return CMP(x,T(0)); }

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

template<typename BinaryFunc, typename UnaryFunc>
auto ON(BinaryFunc&& bf, UnaryFunc&& uf) {
    return [bf=forward<BinaryFunc>(bf),uf=forward<UnaryFunc>(uf)](const auto& x, const auto& y) {
        return bf(uf(x), uf(y));
    };
}

template<typename F>
auto LT_ON(F&& f) {
    return ON(less<>{}, forward<F>(f));
}

template<typename F>
auto GT_ON(F&& f) {
    return ON(greater<>{}, forward<F>(f));
}

template<typename F>
auto EQ_ON(F&& f) {
    return ON(equal_to<>{}, forward<F>(f));
}

template<typename F>
auto NE_ON(F&& f) {
    return ON(not_equal_to<>{}, forward<F>(f));
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

template<typename T, typename Enable=void>
struct ProconHash {
    size_t operator()(const T& x) const noexcept {
        return hash<T>{}(x);
    }
};

template<typename T>
size_t procon_hash_value(const T& x) noexcept {
    return ProconHash<T>{}(x);
}

size_t procon_hash_combine(size_t h1, size_t h2) noexcept {
    constexpr size_t M = UINT64_C(0xc6a4a7935bd1e995);
    constexpr int    R = 47;

    h2 *= M;
    h2 ^= h2 >> R;
    h2 *= M;

    h1 ^= h2;
    h1 *= M;

    h1 += 0xe6546b64;

    return h1;
}

template<typename T1, typename T2>
struct ProconHash<pair<T1,T2>> {
    size_t operator()(const pair<T1,T2>& p) const noexcept {
        size_t h1 = procon_hash_value(p.first);
        size_t h2 = procon_hash_value(p.second);
        return procon_hash_combine(h1, h2);
    }
};

template<typename... TS>
struct ProconHash<tuple<TS...>> {
    size_t operator()(const tuple<TS...>& t) const noexcept {
        size_t h = 0;
        tuple_enumerate(t, [&h](i64, const auto& e) {
            h = procon_hash_combine(h, procon_hash_value(e));
        });
        return h;
    }
};

template<typename C>
struct ProconHash<C,enable_if_t<is_container<C>::value>> {
    size_t operator()(const C& c) const noexcept {
        size_t h = 0;
        for(const auto& e : c)
            h = procon_hash_combine(h, procon_hash_value(e));
        return h;
    }
};

template<typename T, typename Hash=ProconHash<T>, typename Eq=equal_to<T>>
using HashSet = unordered_set<T,Hash,Eq>;
template<typename K, typename V, typename Hash=ProconHash<K>, typename Eq=equal_to<K>>
using HashMap = unordered_map<K,V,Hash,Eq>;
template<typename T, typename Hash=ProconHash<T>, typename Eq=equal_to<T>>
using HashMultiset = unordered_multiset<T,Hash,Eq>;
template<typename K, typename V, typename Hash=ProconHash<K>, typename Eq=equal_to<K>>
using HashMultimap = unordered_multimap<K,V,Hash,Eq>;

template<typename T>
auto vec_make(i64 n, T x) {
    return vector<T>(n, x);
}

template<typename T, typename... Args, SFINAE(sizeof...(Args) >= 2)>
auto vec_make(i64 n, Args... args) {
    auto inner = vec_make<T>(args...);
    return vector<decltype(inner)>(n, inner);
}

template<typename T>
auto vec_reserve(i64 cap) {
    vector<T> res;
    res.reserve(cap);
    return res;
}

template<typename T=i64>
auto vec_iota(i64 n, T init={}) {
    vector<i64> res(n);
    ALL(iota, res, init);
    return res;
}

template<typename T, typename Comp, typename Cont=vector<T>>
auto priority_queue_make(const Comp& comp, Cont&& cont={}) {
    return priority_queue<T,remove_reference_t<Cont>,Comp>(comp, forward<Cont>(cont));
}

template<typename T, typename Comp>
auto priority_queue_reserve(const Comp& comp, i64 cap) {
    return priority_queue<T,vector<T>,Comp>(comp, vec_reserve<T>(cap));
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

// math {{{
/*constexpr*/ i64 GCD(i64 a, i64 b) noexcept {
    /*constexpr*/ auto f_gcd = FIX([](auto&& self, i64 aa, i64 bb) {
        if(bb == 0) return aa;
        return self(bb, aa%bb);
    });
    return f_gcd(ABS(a), ABS(b));
}

/*constexpr*/ i64 LCM(i64 a, i64 b) noexcept {
    ASSERT(a != 0 && b != 0);
    /*constexpr*/ auto f_gcd = FIX([](auto&& self, i64 aa, i64 bb) {
        if(bb == 0) return aa;
        return self(bb, aa%bb);
    });
    a = ABS(a);
    b = ABS(b);
    return a / f_gcd(a,b) * b;
}

/*constexpr*/ tuple<i64,i64,i64> EXTGCD(i64 a, i64 b) noexcept {
    /*constexpr*/ auto impl = FIX([](auto&& self, i64 aa, i64 bb) -> tuple<i64,i64,i64> {
        if(bb == 0) return make_tuple(aa, 1, 0);
        i64 g,x,y; tie(g,x,y) = self(bb, aa%bb);
        return make_tuple(g, y, x-(aa/bb)*y);
    });
    i64 g,x,y; tie(g,x,y) = impl(ABS(a), ABS(b));
    x *= SGN(a);
    y *= SGN(b);
    return make_tuple(g, x, y);
}
// }}}

// string {{{
auto str_reserve(i64 cap) {
    string res;
    res.reserve(cap);
    return res;
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

template<typename T1, typename T2>
struct Scan<pair<T1,T2>> {
    static pair<T1,T2> scan(istream& in) {
        T1 x = Scan<T1>::scan(in);
        T2 y = Scan<T2>::scan(in);
        return {x,y};
    }
};

template<typename T1, typename T2>
struct Scan1<pair<T1,T2>> {
    static pair<T1,T2> scan1(istream& in) {
        T1 x = Scan1<T1>::scan1(in);
        T2 y = Scan1<T2>::scan1(in);
        return {x,y};
    }
};

template<typename... TS>
struct Scan<tuple<TS...>> {
    static tuple<TS...> scan(istream& in) {
        return scan_impl<0>(in);
    }
private:
    template<i64 I, SFINAE(sizeof...(TS) == I)>
    static auto scan_impl(istream&) {
        return make_tuple();
    }
    template<i64 I, SFINAE(sizeof...(TS) > I)>
    static auto scan_impl(istream& in) {
        using T = tuple_element_t<I,tuple<TS...>>;
        auto head = make_tuple(Scan<T>::scan(in));
        return tuple_cat(head, scan_impl<I+1>(in));
    }
};

template<typename... TS>
struct Scan1<tuple<TS...>> {
    static tuple<TS...> scan1(istream& in) {
        return scan1_impl<0>(in);
    }
private:
    template<i64 I, SFINAE(sizeof...(TS) == I)>
    static auto scan1_impl(istream&) {
        return make_tuple();
    }
    template<i64 I, SFINAE(sizeof...(TS) > I)>
    static auto scan1_impl(istream& in) {
        using T = tuple_element_t<I,tuple<TS...>>;
        auto head = make_tuple(Scan1<T>::scan1(in));
        return tuple_cat(head, scan1_impl<I+1>(in));
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
    auto res = vec_reserve<T>(n);
    REP(_, n) {
        res.emplace_back(RD<T>());
    }
    return res;
}

template<typename T=i64>
auto RD1_VEC(i64 n) {
    auto res = vec_reserve<T>(n);
    REP(_, n) {
        res.emplace_back(RD1<T>());
    }
    return res;
}

template<typename T=i64>
auto RD_VEC2(i64 h, i64 w) {
    auto res = vec_reserve<vector<T>>(h);
    REP(_, h) {
        res.emplace_back(RD_VEC<T>(w));
    }
    return res;
}

template<typename T=i64>
auto RD1_VEC2(i64 h, i64 w) {
    auto res = vec_reserve<vector<T>>(h);
    REP(_, h) {
        res.emplace_back(RD1_VEC<T>(w));
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
    Dbg<T>::dbg(out, x);
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

template<typename T, typename C>
struct Dbg<stack<T,C>> {
    static void dbg(ostream& out, stack<T,C> stk) {
        out << "[";
        while(!stk.empty()) {
            dbg_write(out,stk.top()); stk.pop();
            if(!stk.empty()) out << ",";
        }
        out << "]";
    }
};

template<typename T, typename C>
struct Dbg<queue<T,C>> {
    static void dbg(ostream& out, queue<T,C> que) {
        out << "[";
        while(!que.empty()) {
            dbg_write(out,que.front()); que.pop();
            if(!que.empty()) out << ",";
        }
        out << "]";
    }
};

template<typename T, typename C, typename Comp>
struct Dbg<priority_queue<T,C,Comp>> {
    static void dbg(ostream& out, priority_queue<T,C,Comp> que) {
        out << "[";
        while(!que.empty()) {
            dbg_write(out,que.top()); que.pop();
            if(!que.empty()) out << ",";
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

void DBG_IMPL_HELPER() {}

template<typename T, typename... TS>
void DBG_IMPL_HELPER(const T& x, const TS&... args) {
    dbg_write(cerr, x);
    if(sizeof...(args) > 0) {
        cerr << ",";
        DBG_IMPL_HELPER(args...);
    }
}

template<typename... TS>
void DBG_IMPL(i64 line, const char* expr, const TS&... value) {
    cerr << "[L " << line << "]: ";
    cerr << "(" << expr << ") = (";
    DBG_IMPL_HELPER(value...);
    cerr << ")\n";
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

template<typename T>
void DBG_GRID_IMPL(i64 line, const char* expr, const vector<T>& grid) {
    cerr << "[L " << line << "]: ";
    cerr << expr << ":\n";
    for(const auto& row : grid) {
        dbg_write(cerr, row);
        cerr << "\n";
    }
    cerr << "\n";
}

#ifdef PROCON_LOCAL
    #define DBG(args...) DBG_IMPL(__LINE__, CPP_STR_I(args), args)
    #define DBG_DP(args...) DBG_DP_IMPL(__LINE__, CPP_STR_I(args), args)
    #define DBG_GRID(args...) DBG_GRID_IMPL(__LINE__, CPP_STR_I(args), args)
#else
    #define DBG(args...)
    #define DBG_DP(args...)
    #define DBG_GRID(args...)
#endif
// }}}

// modint {{{
template<i64 M>
struct ModIntT {
    static_assert(M >= 2, "");
    i64 v_;  // [0,M)

    ModIntT() : v_(0) {}
    ModIntT(i64 v) {
        i64 r = v % M;
        v_ = r >= 0 ? r : r+M;
    }

    ModIntT operator-() const {
        return ModIntT(-v_);
    }
    ModIntT& operator+=(ModIntT rhs) {
        v_ += rhs.v_;
        v_ %= M;
        return *this;
    }
    ModIntT& operator-=(ModIntT rhs) {
        v_ += M;
        v_ -= rhs.v_;
        v_ %= M;
        return *this;
    }
    ModIntT& operator*=(ModIntT rhs) {
        v_ *= rhs.v_;
        v_ %= M;
        return *this;
    }

    ModIntT& operator++() {
        return *this += 1;
    }
    ModIntT& operator--() {
        return *this -= 1;
    }
    ModIntT operator++(int) {
        return exchange(*this, *this+1);
    }
    ModIntT operator--(int) {
        return exchange(*this, *this-1);
    }

    explicit operator i64() const { return v_; }

    ModIntT inv() const {
        i64 g,x; tie(g,x,ignore) = EXTGCD(v_, M);
        ASSERT(g == 1);
        return ModIntT(x);
    }
};

template<i64 M>
ModIntT<M> operator+(ModIntT<M> lhs, ModIntT<M> rhs) { return ModIntT<M>(lhs) += rhs; }
template<i64 M>
ModIntT<M> operator+(ModIntT<M> lhs, i64 rhs) { return ModIntT<M>(lhs) += rhs; }
template<i64 M>
ModIntT<M> operator+(i64 lhs, ModIntT<M> rhs) { return ModIntT<M>(rhs) += lhs; }
template<i64 M>
ModIntT<M> operator-(ModIntT<M> lhs, ModIntT<M> rhs) { return ModIntT<M>(lhs) -= rhs; }
template<i64 M>
ModIntT<M> operator-(ModIntT<M> lhs, i64 rhs) { return ModIntT<M>(lhs) -= rhs; }
template<i64 M>
ModIntT<M> operator-(i64 lhs, ModIntT<M> rhs) { return ModIntT<M>(rhs) -= lhs; }
template<i64 M>
ModIntT<M> operator*(ModIntT<M> lhs, ModIntT<M> rhs) { return ModIntT<M>(lhs) *= rhs; }
template<i64 M>
ModIntT<M> operator*(ModIntT<M> lhs, i64 rhs) { return ModIntT<M>(lhs) *= rhs; }
template<i64 M>
ModIntT<M> operator*(i64 lhs, ModIntT<M> rhs) { return ModIntT<M>(rhs) *= lhs; }

template<i64 M>
bool operator==(ModIntT<M> lhs, ModIntT<M> rhs) { return lhs.v_ == rhs.v_; }
template<i64 M>
bool operator==(ModIntT<M> lhs, i64 rhs) { return lhs == ModIntT<M>(rhs); }
template<i64 M>
bool operator==(i64 lhs, ModIntT<M> rhs) { return ModIntT<M>(lhs) == rhs; }
template<i64 M>
bool operator!=(ModIntT<M> lhs, ModIntT<M> rhs) { return !(lhs == rhs); }
template<i64 M>
bool operator!=(ModIntT<M> lhs, i64 rhs) { return !(lhs == rhs); }
template<i64 M>
bool operator!=(i64 lhs, ModIntT<M> rhs) { return !(lhs == rhs); }

template<i64 M>
struct Scan<ModIntT<M>> {
    static ModIntT<M> scan(istream& in) {
        return Scan<i64>::scan(in);
    }
};

template<i64 M>
struct Fmt<ModIntT<M>> {
    static void fmt(ostream& out, ModIntT<M> x) {
        fmt_write(out, x.v_);
    }
};

template<i64 M>
struct Dbg<ModIntT<M>> {
    static void dbg(ostream& out, ModIntT<M> x) {
        dbg_write(out, x.v_);
    }
};

using ModInt = ModIntT<MOD>;
// }}}
// }}}

// init {{{
struct ProconInit {
    static constexpr int IOS_PREC = 15;
    static constexpr bool AUTOFLUSH = false;

    ProconInit() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cin.exceptions(ios::failbit | ios::badbit);
        cout << fixed << setprecision(IOS_PREC);
#ifdef PROCON_LOCAL
        cerr << fixed << setprecision(2);
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
