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
#ifdef __SIZEOF_INT128__
using i128 = __int128;
using u128 = unsigned __int128;
#endif

using f32 = float;
using f64 = double;
using f80 = long double;
// }}}

using Real = f80;

template<class T> constexpr T PROCON_INF();
template<> constexpr i64  PROCON_INF<i64>()  { return INT64_C(1'010'000'000'000'000'017); }
template<> constexpr Real PROCON_INF<Real>() { return Real(1e100L); }

constexpr i64  INF  = PROCON_INF<i64>();
constexpr Real FINF = PROCON_INF<Real>();

constexpr i64 MOD = INT64_C(1'000'000'007);
//constexpr i64 MOD = INT64_C(998'244'353);

constexpr Real EPS = Real(1e-10L);

// util {{{
constexpr Real PI = Real(3.141592653589793238462643383279502884197L);

bool LT_EPS(Real lhs, Real rhs, Real eps=EPS) { return lhs < rhs-eps; }
bool GT_EPS(Real lhs, Real rhs, Real eps=EPS) { return lhs > rhs+eps; }
bool EQ_EPS(Real lhs, Real rhs, Real eps=EPS) { return std::abs(lhs-rhs) <= eps; }

bool EQ_EXACT(Real lhs, Real rhs) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
    return lhs == rhs;
#pragma GCC diagnostic pop
}

#define FOR(i, start, end) for(i64 i = (start), CPP_CAT(i,xxxx_end)=(end); i < CPP_CAT(i,xxxx_end); ++i)
#define REP(i, n) FOR(i, 0, n)

#define ALL(f,c,...) (([&](decltype((c)) cccc) { return (f)(std::begin(cccc), std::end(cccc), ## __VA_ARGS__); })(c))

#define LIFT(f) ([](auto&&... args) -> decltype(auto) { return (f)(std::forward<decltype(args)>(args)...); })

template<class C>
constexpr i64 SIZE(const C& c) noexcept { return static_cast<i64>(c.size()); }

template<class T, size_t N>
constexpr i64 SIZE(const T (&)[N]) noexcept { return static_cast<i64>(N); }

constexpr bool is_odd (i64 x) { return x%2 != 0; }
constexpr bool is_even(i64 x) { return x%2 == 0; }

template<class T, SFINAE(is_signed<T>::value)>
constexpr T ABS(T x) noexcept {
    return x < 0 ? -x : x;
}

template<class T>
constexpr i64 CMP(T x, T y) noexcept { return (y<x) - (x<y); }

template<class T>
constexpr i64 SGN(T x) noexcept { return CMP(x,T(0)); }

template<class T1, class T2, class Comp=less<>,
         SFINAE(
             is_arithmetic<T1>::value &&
             is_arithmetic<T2>::value &&
             is_signed<T1>::value != is_unsigned<T2>::value
         )>
constexpr auto MAX(T1 x, T2 y, Comp comp={}) {
    return max<common_type_t<T1,T2>>({x,y}, comp);
}

template<class T, class Comp=less<>>
constexpr const T& MAX(const T& x, const T& y, Comp comp={}) {
    return max(x, y, comp);
}

template<class T, class Comp=less<>>
constexpr T MAX(initializer_list<T> ilist, Comp comp={}) {
    return max(ilist, comp);
}

template<class T1, class T2, class Comp=less<>,
         SFINAE(
             is_arithmetic<T1>::value &&
             is_arithmetic<T2>::value &&
             is_signed<T1>::value != is_unsigned<T2>::value
         )>
constexpr auto MIN(T1 x, T2 y, Comp comp={}) {
    return min<common_type_t<T1,T2>>({x,y}, comp);
}

template<class T, class Comp=less<>>
constexpr const T& MIN(const T& x, const T& y, Comp comp={}) {
    return min(x, y, comp);
}

template<class T, class Comp=less<>>
constexpr T MIN(initializer_list<T> ilist, Comp comp={}) {
    return min(ilist, comp);
}

template<class T, class U, class Comp=less<>>
constexpr bool chmax(T& xmax, const U& x, Comp comp={}) noexcept {
    if(comp(xmax, x)) {
        xmax = x;
        return true;
    }
    return false;
}

template<class T, class U, class Comp=less<>>
constexpr bool chmin(T& xmin, const U& x, Comp comp={}) noexcept {
    if(comp(x, xmin)) {
        xmin = x;
        return true;
    }
    return false;
}

template<class BinaryFunc, class UnaryFunc>
auto ON(BinaryFunc&& bf, UnaryFunc&& uf) {
    return [bf=forward<BinaryFunc>(bf),uf=forward<UnaryFunc>(uf)](const auto& x, const auto& y) {
        return bf(uf(x), uf(y));
    };
}

template<class F>
auto LT_ON(F&& f) {
    return ON(less<>{}, forward<F>(f));
}

template<class F>
auto GT_ON(F&& f) {
    return ON(greater<>{}, forward<F>(f));
}

template<class F>
auto NOT_FN(F&& f) {
    return [f=forward<F>(f)](auto&&... args) -> bool { return !f(forward<decltype(args)>(args)...); };
}

// ビット演算 {{{
// 引数は [-INF,INF] のみ想定
i64 BIT_I(i64 i) {
    return 1LL << i;
}

i64 BIT_I_1(i64 i) {
    return BIT_I(i) - 1;
}

i64 BIT_GET(i64 x, i64 i) {
    return x & BIT_I(i);
}

bool BIT_TEST(i64 x, i64 i) {
    return BIT_GET(x,i) != 0;
}

i64 BIT_SET(i64 x, i64 i) {
    return x | BIT_I(i);
}

i64 BIT_CLEAR(i64 x, i64 i) {
    return x & ~BIT_I(i);
}

i64 BIT_FLIP(i64 x, i64 i) {
    return x ^ BIT_I(i);
}

i64 BIT_ASSIGN(i64 x, i64 i, bool b) {
    return b ? BIT_SET(x,i) : BIT_CLEAR(x,i);
}

i64 BIT_COUNT_LEADING_ZEROS(i64 x) {
    if(x == 0) return 64;
    return __builtin_clzll(x);
}

i64 BIT_COUNT_LEADING_ONES(i64 x) {
    return BIT_COUNT_LEADING_ZEROS(~x);
}

i64 BIT_COUNT_TRAILING_ZEROS(i64 x) {
    if(x == 0) return 64;
    return __builtin_ctzll(x);
}

i64 BIT_COUNT_TRAILING_ONES(i64 x) {
    return BIT_COUNT_TRAILING_ZEROS(~x);
}

i64 BIT_COUNT_ONES(i64 x) {
    return __builtin_popcountll(x);
}

i64 BIT_COUNT_ZEROS(i64 x) {
    return 64 - BIT_COUNT_ONES(x);
}

// 1の個数が奇数なら1, 偶数なら0を返す
i64 BIT_PARITY(i64 x) {
    return __builtin_parityll(x);
}

// X ⊆ {0,1,...,n-1}, |X| = k なる部分集合 X を昇順に列挙する
// comb(n,k) 個
//
// ```
// i64 x = BIT_I_1(3);
// do {
//     // ...
// } while(BIT_NEXT_SET_SIZED(x, 10));
// ```
bool BIT_NEXT_SET_SIZED(i64& x, i64 n) {
    if(x == 0) return false;
    i64 t = (x|(x-1)) + 1;
    x = t | ((~x&(x-1)) >> (BIT_COUNT_TRAILING_ZEROS(x)+1));
    return x < BIT_I(n);
}

// 集合 Y の部分集合 X を昇順に列挙する
// 2^|Y| 個
//
// ```
// i64 y = 0b10101;
// i64 x = 0;
// do {
//     // ...
// } while(BIT_NEXT_SUBSET(x, y));
// ```
bool BIT_NEXT_SUBSET(i64& x, i64 y) {
    if(x == y) return false;
    x = (x-y) & y;
    return true;
}

// 集合 Y の部分集合 X を降順に列挙する
// 2^|Y| 個
//
// ```
// i64 y = 0b10101;
// i64 x = y;
// do {
//     // ...
// } while(BIT_PREV_SUBSET(x, y));
// ```
bool BIT_PREV_SUBSET(i64& x, i64 y) {
    if(x == 0) return false;
    x = (x-1) & y;
    return true;
}

// 集合 Y を包含する集合 X ⊆ {0,1,...,n-1} を昇順に列挙する
// 2^(n-|Y|) 個
//
// ```
// i64 y = 0b00010101;
// i64 x = y;
// do {
//     // ...
// } while(BIT_NEXT_SUPERSET(x, 8, y));
// ```
bool BIT_NEXT_SUPERSET(i64& x, i64 n, i64 y) {
    x = (x+1) | y;
    return x < BIT_I(n);
}
// }}}

// lo:OK, hi:NG
template<class Pred>
i64 bisect_integer(i64 lo, i64 hi, Pred pred) {
    ASSERT(lo < hi);

    while(lo+1 < hi) {
        i64 mid = (lo+hi) / 2;
        if(pred(mid))
            lo = mid;
        else
            hi = mid;
    }
    return lo;
}

template<class Pred>
Real bisect_real(Real lo, Real hi, Pred pred, i64 iter=70) {
    ASSERT(lo < hi);

    REP(_, iter) {
        Real mid = (lo+hi) / 2;
        if(pred(mid))
            lo = mid;
        else
            hi = mid;
    }
    return lo;
}

// Haskell の divMod と同じ
pair<i64,i64> divmod(i64 a, i64 b) {
    i64 q = a / b;
    i64 r = a % b;
    if((b>0 && r<0) || (b<0 && r>0)) {
        --q;
        r += b;
    }
    return {q,r};
}

i64 div_ceil(i64 a, i64 b) {
    i64 q = a / b;
    i64 r = a % b;
    if((b>0 && r>0) || (b<0 && r<0))
        ++q;
    return q;
}

i64 div_floor(i64 a, i64 b) {
    return divmod(a,b).first;
}

i64 modulo(i64 a, i64 b) {
    return divmod(a,b).second;
}

i64 align_ceil(i64 x, i64 align) {
    ASSERT(align > 0);
    return div_ceil(x,align) * align;
}

i64 align_floor(i64 x, i64 align) {
    ASSERT(align > 0);
    return div_floor(x,align) * align;
}

template<class InputIt, class BinaryOp>
auto FOLD(InputIt first, InputIt last,
          typename iterator_traits<InputIt>::value_type init,
          BinaryOp op)
{
    for(; first != last; ++first)
        init = op(move(init), *first);
    return init;
}

template<class InputIt, class BinaryOp>
auto FOLD1(InputIt first, InputIt last, BinaryOp op) {
    auto init = *first++;
    return FOLD(first, last, init, op);
}

template<class InputIt>
auto SUM(InputIt first, InputIt last) {
    return FOLD1(first, last, plus<>{});
}

template<class C>
void UNIQ(C& c) {
    c.erase(ALL(unique,c), end(c));
}

template<class C>
void SORT_UNIQ(C& c) {
    ALL(sort, c);
    UNIQ(c);
}

// tuple {{{
template<i64 I=0, class F, class... TS, SFINAE(sizeof...(TS) == I)>
void tuple_enumerate(tuple<TS...>&, F&&) {}

template<i64 I=0, class F, class... TS, SFINAE(sizeof...(TS) > I)>
void tuple_enumerate(tuple<TS...>& t, F&& f) {
    f(I, get<I>(t));
    tuple_enumerate<I+1>(t, forward<F>(f));
}

template<i64 I=0, class F, class... TS, SFINAE(sizeof...(TS) == I)>
void tuple_enumerate(const tuple<TS...>&, F&&) {}

template<i64 I=0, class F, class... TS, SFINAE(sizeof...(TS) > I)>
void tuple_enumerate(const tuple<TS...>& t, F&& f) {
    f(I, get<I>(t));
    tuple_enumerate<I+1>(t, forward<F>(f));
}
// }}}

// container {{{
template<class T> struct is_container : false_type {};
template<class T, size_t N> struct is_container<array<T,N>> : true_type {};
template<class... Args> struct is_container<vector<Args...>> : true_type {};
template<class... Args> struct is_container<deque<Args...>> : true_type {};
template<class... Args> struct is_container<list<Args...>> : true_type {};
template<class... Args> struct is_container<forward_list<Args...>> : true_type {};
template<class... Args> struct is_container<set<Args...>> : true_type {};
template<class... Args> struct is_container<multiset<Args...>> : true_type {};
template<class... Args> struct is_container<unordered_set<Args...>> : true_type {};
template<class... Args> struct is_container<unordered_multiset<Args...>> : true_type {};
template<class... Args> struct is_container<map<Args...>> : true_type {};
template<class... Args> struct is_container<multimap<Args...>> : true_type {};
template<class... Args> struct is_container<unordered_map<Args...>> : true_type {};
template<class... Args> struct is_container<unordered_multimap<Args...>> : true_type {};

template<class T, class Enable=void>
struct ProconHash {
    size_t operator()(const T& x) const noexcept {
        return hash<T>{}(x);
    }
};

template<class T>
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

template<class T1, class T2>
struct ProconHash<pair<T1,T2>> {
    size_t operator()(const pair<T1,T2>& p) const noexcept {
        size_t h1 = procon_hash_value(p.first);
        size_t h2 = procon_hash_value(p.second);
        return procon_hash_combine(h1, h2);
    }
};

template<class... TS>
struct ProconHash<tuple<TS...>> {
    size_t operator()(const tuple<TS...>& t) const noexcept {
        size_t h = 0;
        tuple_enumerate(t, [&h](i64, const auto& e) {
            h = procon_hash_combine(h, procon_hash_value(e));
        });
        return h;
    }
};

template<class C>
struct ProconHash<C,enable_if_t<is_container<C>::value>> {
    size_t operator()(const C& c) const noexcept {
        size_t h = 0;
        for(const auto& e : c)
            h = procon_hash_combine(h, procon_hash_value(e));
        return h;
    }
};

template<class T, class Hash=ProconHash<T>, class Eq=equal_to<T>>
using HashSet = unordered_set<T,Hash,Eq>;
template<class K, class V, class Hash=ProconHash<K>, class Eq=equal_to<K>>
using HashMap = unordered_map<K,V,Hash,Eq>;
template<class T, class Hash=ProconHash<T>, class Eq=equal_to<T>>
using HashMultiset = unordered_multiset<T,Hash,Eq>;
template<class K, class V, class Hash=ProconHash<K>, class Eq=equal_to<K>>
using HashMultimap = unordered_multimap<K,V,Hash,Eq>;

template<class T>
auto vec_make(i64 n, T x) {
    return vector<T>(n, x);
}

template<class T, class... Args, SFINAE(sizeof...(Args) >= 2)>
auto vec_make(i64 n, Args... args) {
    auto inner = vec_make<T>(args...);
    return vector<decltype(inner)>(n, inner);
}

template<class T>
auto vec_reserve(i64 cap) {
    vector<T> res;
    res.reserve(cap);
    return res;
}

template<class T=i64>
auto vec_iota(i64 n, T init={}) {
    vector<i64> res(n);
    ALL(iota, res, init);
    return res;
}

template<class T, class Comp, class Cont=vector<T>>
auto priority_queue_make(const Comp& comp, Cont&& cont={}) {
    return priority_queue<T,remove_reference_t<Cont>,Comp>(comp, forward<Cont>(cont));
}

template<class T, class Comp>
auto priority_queue_reserve(const Comp& comp, i64 cap) {
    return priority_queue<T,vector<T>,Comp>(comp, vec_reserve<T>(cap));
}

template<class T, size_t N, size_t... NS>
struct ArrayType {
    using type = array<class ArrayType<T,NS...>::type,N>;
};

template<class T, size_t N>
struct ArrayType<T,N> {
    using type = array<T,N>;
};

template<class T, size_t... NS>
using Array = typename ArrayType<T,NS...>::type;

template<class T, size_t N>
T& array_at(Array<T,N>& ary, i64 i) {
    return ary[i];
}

template<class T, size_t N, size_t... NS, class... Args>
T& array_at(Array<T,N,NS...>& ary, i64 i, Args... args) {
    return array_at<T,NS...>(ary[i], args...);
}

template<class T, size_t N>
const T& array_at(const Array<T,N>& ary, i64 i) {
    return ary[i];
}

template<class T, size_t N, size_t... NS, class... Args>
const T& array_at(const Array<T,N,NS...>& ary, i64 i, Args... args) {
    return array_at<T,NS...>(ary[i], args...);
}

template<class T, class C>
T POP(stack<T,C>& stk) {
    T x = stk.top(); stk.pop();
    return x;
}

template<class T, class C>
T POP(queue<T,C>& que) {
    T x = que.front(); que.pop();
    return x;
}

template<class T, class C, class Comp>
T POP(priority_queue<T,C,Comp>& que) {
    T x = que.top(); que.pop();
    return x;
}
// }}}

// fixpoint {{{
template<class F>
class FixPoint {
public:
    explicit constexpr FixPoint(F&& f) : f_(forward<F>(f)) {}

    template<class... Args>
    constexpr decltype(auto) operator()(Args&&... args) const {
        return f_(*this, forward<Args>(args)...);
    }

private:
    F f_;
};

template<class F>
constexpr decltype(auto) FIX(F&& f) {
    return FixPoint<F>(forward<F>(f));
}

template<class F, size_t... NS>
class FixPointMemo {
public:
    explicit FixPointMemo(F&& f) : f_(forward<F>(f)) {}

    template<class... Args>
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

template<size_t... NS, class F>
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
char chr_digit(i64 n)  { return char('0'+n); }
i64  ord_digit(char c) { return c-'0'; }
char chr_lower(i64 n)  { return char('a'+n); }
i64  ord_lower(char c) { return c-'a'; }
char chr_upper(i64 n)  { return char('A'+n); }
i64  ord_upper(char c) { return c-'A'; }

auto str_reserve(i64 cap) {
    string res;
    res.reserve(cap);
    return res;
}
// }}}

// input {{{
template<class T, class Enable=void>
struct Scan {
    static T scan(istream& in) {
        T res;
        in >> res;
        return res;
    }
};

template<class T, class Enable=void>
struct Scan1;

template<class T>
struct Scan1<T,enable_if_t<is_integral<T>::value && !is_same<T,bool>::value>> {
    static T scan1(istream& in) {
        return Scan<T>::scan(in) - 1;
    }
};

template<class T1, class T2>
struct Scan<pair<T1,T2>> {
    static pair<T1,T2> scan(istream& in) {
        T1 x = Scan<T1>::scan(in);
        T2 y = Scan<T2>::scan(in);
        return {x,y};
    }
};

template<class T1, class T2>
struct Scan1<pair<T1,T2>> {
    static pair<T1,T2> scan1(istream& in) {
        T1 x = Scan1<T1>::scan1(in);
        T2 y = Scan1<T2>::scan1(in);
        return {x,y};
    }
};

template<class T>
tuple<T> tuple_scan_impl(istream& in) {
    return make_tuple(Scan<T>::scan(in));
}

template<class T, class... TS, SFINAE(sizeof...(TS) > 0)>
tuple<T,TS...> tuple_scan_impl(istream& in) {
    auto head = make_tuple(Scan<T>::scan(in));
    return tuple_cat(head, tuple_scan_impl<TS...>(in));
}

template<class... TS>
struct Scan<tuple<TS...>> {
    static tuple<TS...> scan(istream& in) {
        return tuple_scan_impl<TS...>(in);
    }
};

template<class T>
tuple<T> tuple_scan1_impl(istream& in) {
    return make_tuple(Scan1<T>::scan1(in));
}

template<class T, class... TS, SFINAE(sizeof...(TS) > 0)>
tuple<T,TS...> tuple_scan1_impl(istream& in) {
    auto head = make_tuple(Scan1<T>::scan1(in));
    return tuple_cat(head, tuple_scan1_impl<TS...>(in));
}

template<class... TS>
struct Scan1<tuple<TS...>> {
    static tuple<TS...> scan1(istream& in) {
        return tuple_scan1_impl<TS...>(in);
    }
};

template<class T=i64>
T RD() {
    return Scan<T>::scan(cin);
}

template<class T=i64>
T RD1() {
    return Scan1<T>::scan1(cin);
}

template<class T=i64>
auto RD_VEC(i64 n) {
    auto res = vec_reserve<T>(n);
    REP(_, n) {
        res.emplace_back(RD<T>());
    }
    return res;
}

template<class T=i64>
auto RD1_VEC(i64 n) {
    auto res = vec_reserve<T>(n);
    REP(_, n) {
        res.emplace_back(RD1<T>());
    }
    return res;
}

template<class T=i64>
auto RD_VEC2(i64 h, i64 w) {
    auto res = vec_reserve<vector<T>>(h);
    REP(_, h) {
        res.emplace_back(RD_VEC<T>(w));
    }
    return res;
}

template<class T=i64>
auto RD1_VEC2(i64 h, i64 w) {
    auto res = vec_reserve<vector<T>>(h);
    REP(_, h) {
        res.emplace_back(RD1_VEC<T>(w));
    }
    return res;
}
// }}}

// output {{{
template<class T, class Enable=void>
struct Fmt {
    static void fmt(ostream& out, const T& x) { out << x; }
};

template<class T>
void fmt_write(ostream& out, const T& x) {
    Fmt<T>::fmt(out, x);
}

template<class... TS>
struct Fmt<tuple<TS...>> {
    static void fmt(ostream& out, const tuple<TS...>& t) {
        tuple_enumerate(t, [&out](i64 i, const auto& e) {
            if(i != 0) out << ' ';
            fmt_write(out, e);
        });
    }
};

template<class T1, class T2>
struct Fmt<pair<T1,T2>> {
    static void fmt(ostream& out, const pair<T1,T2>& p) {
        return fmt_write(out, make_tuple(p.first,p.second));
    }
};

template<class C>
struct Fmt<C,enable_if_t<is_container<C>::value>> {
    static void fmt(ostream& out, const C& c) {
        for(auto it = begin(c); it != end(c); ++it) {
            if(it != begin(c)) out << ' ';
            fmt_write(out, *it);
        }
    }
};

void PRINT() {}

template<class T, class... TS>
void PRINT(const T& x, const TS&... args) {
    fmt_write(cout, x);
    if(sizeof...(args) > 0) {
        cout << ' ';
        PRINT(args...);
    }
}

template<class... TS>
void PRINTLN(const TS&... args) {
    PRINT(args...);
    cout << '\n';
}
// }}}

// debug {{{
template<class T, class Enable=void>
struct Dbg {
    static void dbg(ostream& out, const T& x) { out << x; }
};

template<class T>
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
struct Dbg<Real> {
    static void dbg(ostream& out, Real x) {
        if(EQ_EXACT(x, FINF))
            out << "FINF";
        else if(EQ_EXACT(x, -FINF))
            out << "-FINF";
        else
            out << x;
    }
};

template<class T, size_t N>
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

template<size_t N>
struct Dbg<char[N]> {
    static void dbg(ostream& out, const char (&s)[N]) {
        out << s;
    }
};

template<class... TS>
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

template<class T1, class T2>
struct Dbg<pair<T1,T2>> {
    static void dbg(ostream& out, const pair<T1,T2>& p) {
        return dbg_write(out, make_tuple(p.first,p.second));
    }
};

template<class C>
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

template<class T, class C>
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

template<class T, class C>
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

template<class T, class C, class Comp>
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

template<class T>
void DBG_IMPL(i64 line, const char* expr, const T& value) {
    cerr << "[L " << line << "]: ";
    cerr << expr << " = ";
    dbg_write(cerr, value);
    cerr << "\n";
}

void DBG_IMPL_HELPER() {}

template<class T, class... TS>
void DBG_IMPL_HELPER(const T& x, const TS&... args) {
    dbg_write(cerr, x);
    if(sizeof...(args) > 0) {
        cerr << ",";
        DBG_IMPL_HELPER(args...);
    }
}

template<class... TS>
void DBG_IMPL(i64 line, const char* expr, const TS&... value) {
    cerr << "[L " << line << "]: ";
    cerr << "(" << expr << ") = (";
    DBG_IMPL_HELPER(value...);
    cerr << ")\n";
}

template<size_t N, class T, SFINAE(rank<T>::value == 0)>
void DBG_DP_IMPL_HELPER(ostream& out, const T& x, const array<i64,N>&, const array<i64,N>&) {
    dbg_write(out, x);
}

template<size_t N, class T, SFINAE(rank<T>::value > 0)>
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

template<class T, SFINAE(rank<T>::value > 0)>
void DBG_DP_IMPL(i64 line, const char* expr, const T& dp,
                 const array<i64,rank<T>::value>& sizes={},
                 const array<i64,rank<T>::value>& offs={})
{
    cerr << "[L " << line << "]: ";
    cerr << expr << " = ";
    DBG_DP_IMPL_HELPER<rank<T>::value>(cerr, dp, sizes, offs);
    cerr << "\n";
}

template<class T>
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
template<class Mod>
class ModIntT {
private:
    i64 v_;  // [0,Mod::value)

    static i64 mod() { return Mod::value; }

    static i64 normalize(i64 x) {
        i64 res = x % mod();
        if(res < 0) res += mod();
        return res;
    }

public:
    ModIntT() : v_(0) {}
    ModIntT(i64 v) : v_(normalize(v)) {}

    explicit operator i64() const { return v_; }

    ModIntT operator-() const { return ModIntT(-v_); }

    ModIntT& operator+=(ModIntT rhs) {
        v_ = normalize(v_ + rhs.v_);
        return *this;
    }
    ModIntT& operator-=(ModIntT rhs) {
        v_ = normalize(v_ - rhs.v_);
        return *this;
    }
    ModIntT& operator*=(ModIntT rhs) {
        v_ = normalize(v_ * rhs.v_);
        return *this;
    }

    ModIntT& operator++() { return *this += 1; }
    ModIntT& operator--() { return *this -= 1; }
    ModIntT operator++(int) { return exchange(*this, *this+1); }
    ModIntT operator--(int) { return exchange(*this, *this-1); }

    ModIntT inv() const {
        i64 g,x; tie(g,x,ignore) = EXTGCD(v_, mod());
        ASSERT(g == 1);
        return ModIntT(x);
    }

    friend ModIntT operator+(ModIntT lhs, ModIntT rhs) { return ModIntT(lhs) += rhs; }
    friend ModIntT operator+(ModIntT lhs, i64 rhs)     { return ModIntT(lhs) += rhs; }
    friend ModIntT operator+(i64 lhs, ModIntT rhs)     { return ModIntT(rhs) += lhs; }
    friend ModIntT operator-(ModIntT lhs, ModIntT rhs) { return ModIntT(lhs) -= rhs; }
    friend ModIntT operator-(ModIntT lhs, i64 rhs)     { return ModIntT(lhs) -= rhs; }
    friend ModIntT operator-(i64 lhs, ModIntT rhs)     { return ModIntT(rhs) -= lhs; }
    friend ModIntT operator*(ModIntT lhs, ModIntT rhs) { return ModIntT(lhs) *= rhs; }
    friend ModIntT operator*(ModIntT lhs, i64 rhs)     { return ModIntT(lhs) *= rhs; }
    friend ModIntT operator*(i64 lhs, ModIntT rhs)     { return ModIntT(rhs) *= lhs; }

    friend bool operator==(ModIntT lhs, ModIntT rhs) { return i64(lhs) == i64(rhs); }
    friend bool operator==(ModIntT lhs, i64 rhs)     { return lhs == ModIntT(rhs); }
    friend bool operator==(i64 lhs, ModIntT rhs)     { return ModIntT(lhs) == rhs; }
    friend bool operator!=(ModIntT lhs, ModIntT rhs) { return !(lhs == rhs); }
    friend bool operator!=(ModIntT lhs, i64 rhs)     { return !(lhs == rhs); }
    friend bool operator!=(i64 lhs, ModIntT rhs)     { return !(lhs == rhs); }
};

template<class Mod>
struct ProconHash<ModIntT<Mod>> {
    size_t operator()(ModIntT<Mod> x) const noexcept {
        return procon_hash_value(i64(x));
    }
};

template<class Mod>
struct Scan<ModIntT<Mod>> {
    static ModIntT<Mod> scan(istream& in) {
        i64 v = Scan<i64>::scan(in);
        return ModIntT<Mod>(v);
    }
};

template<class Mod>
struct Fmt<ModIntT<Mod>> {
    static void fmt(ostream& out, ModIntT<Mod> x) {
        fmt_write(out, i64(x));
    }
};

template<class Mod>
struct Dbg<ModIntT<Mod>> {
    static void dbg(ostream& out, ModIntT<Mod> x) {
        dbg_write(out, i64(x));
    }
};

template<i64 M>
using ModIntC = ModIntT<integral_constant<i64,M>>;

using ModInt = ModIntC<MOD>;
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
