// procon {{{

static_assert(is_same<Int,i64>::value || is_same<Int,i32>::value);
static_assert(is_same<Real,f80>::value || is_same<Real,f64>::value || is_same<Real,f32>::value);

#define CPP_STR(x) CPP_STR_I(x)
#define CPP_CAT(x,y) CPP_CAT_I(x,y)
#define CPP_STR_I(args...) #args
#define CPP_CAT_I(x,y) x ## y

#define SFINAE(pred...) std::enable_if_t<(pred), std::nullptr_t> = nullptr

#define ASSERT(expr...) assert((expr))
#if defined(PROCON_LOCAL) || ASSERT_LV >= 2
# define ASSERT_LOCAL(expr...) assert((expr))
#else
# define ASSERT_LOCAL(expr...)
#endif

constexpr Int  INF  = PROCON_INF<Int>();
constexpr Real FINF = PROCON_INF<Real>();

constexpr Real PI = Real(3.141592653589793238462643383279502884197L);

template<class T> constexpr T SQRT_MAX();
template<> constexpr i32 SQRT_MAX<i32>() { return 46340; }
template<> constexpr i64 SQRT_MAX<i64>() { return INT64_C(3037000499); }

template<class T, SFINAE(is_signed<T>::value)>
constexpr T ABS(T x) noexcept {
    return x < 0 ? -x : x;
}

constexpr bool LT_EPS(Real lhs, Real rhs, Real eps=EPS) { return lhs < rhs-eps; }
constexpr bool GT_EPS(Real lhs, Real rhs, Real eps=EPS) { return lhs > rhs+eps; }
constexpr bool EQ_EPS(Real lhs, Real rhs, Real eps=EPS) { return ABS(lhs-rhs) <= eps; }

constexpr bool EQ_EXACT(Real lhs, Real rhs) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
    return lhs == rhs;
#pragma GCC diagnostic pop
}

#define FOR(i, start, end) for(Int i = (start), CPP_CAT(i,xxxx_end)=(end); i < CPP_CAT(i,xxxx_end); ++i)
#define REP(i, n) FOR(i, 0, n)
#define LOOP(n) REP(CPP_CAT(macro_loop_counter,__COUNTER__), n)

#define ALL(f,c,...) (([&](decltype((c)) cccc) { return (f)(std::begin(cccc), std::end(cccc), ## __VA_ARGS__); })(c))
#define SLICE(f,c,l,r,...) (([&](decltype((c)) cccc, decltype((l)) llll, decltype((r)) rrrr) {\
    auto iiii = llll <= rrrr ? std::begin(cccc)+llll : std::end(cccc);\
    auto jjjj = llll <= rrrr ? std::begin(cccc)+rrrr : std::end(cccc);\
    return (f)(iiii, jjjj, ## __VA_ARGS__);\
})(c,l,r))

#define LIFT(f) ([](auto&&... args) -> decltype(auto) { return (f)(std::forward<decltype(args)>(args)...); })

template<class C>
constexpr Int SIZE(const C& c) noexcept { return Int(c.size()); }

template<class T, size_t N>
constexpr Int SIZE(const T (&)[N]) noexcept { return Int(N); }

constexpr bool is_odd (Int x) { return x%2 != 0; }
constexpr bool is_even(Int x) { return x%2 == 0; }

template<class T>
constexpr Int CMP(T x, T y) noexcept { return (y<x) - (x<y); }

template<class T>
constexpr Int SGN(T x) noexcept { return CMP(x,T(0)); }

template<class T1, class T2, class Comp=less<>,
         SFINAE(
             is_integral<T1>::value &&
             is_integral<T2>::value &&
             is_signed<T1>::value != is_unsigned<T2>::value
         )>
constexpr auto MAX(T1 x, T2 y, Comp comp={}) {
    return max<common_type_t<T1,T2>>({x,y}, comp);
}

template<class T1, class T2, class Comp=less<>,
         SFINAE(
             is_floating_point<T1>::value &&
             is_floating_point<T2>::value
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
             is_integral<T1>::value &&
             is_integral<T2>::value &&
             is_signed<T1>::value != is_unsigned<T2>::value
         )>
constexpr auto MIN(T1 x, T2 y, Comp comp={}) {
    return min<common_type_t<T1,T2>>({x,y}, comp);
}

template<class T1, class T2, class Comp=less<>,
         SFINAE(
             is_floating_point<T1>::value &&
             is_floating_point<T2>::value
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

struct IDENTITY {
    using is_transparent = void;

    template<class T>
    constexpr decltype(auto) operator()(T&& x) const { return forward<T>(x); }
};

// ビット演算 {{{
// 引数は [-INF,INF] のみ想定
constexpr Int BIT_I(Int i) {
    return Int(1) << i;
}

constexpr Int BIT_I_1(Int i) {
    return BIT_I(i) - 1;
}

constexpr Int BIT_GET(Int x, Int i) {
    return x & BIT_I(i);
}

constexpr bool BIT_TEST(Int x, Int i) {
    return BIT_GET(x,i) != 0;
}

constexpr Int BIT_SET(Int x, Int i) {
    return x | BIT_I(i);
}

constexpr Int BIT_CLEAR(Int x, Int i) {
    return x & ~BIT_I(i);
}

constexpr Int BIT_FLIP(Int x, Int i) {
    return x ^ BIT_I(i);
}

constexpr Int BIT_ASSIGN(Int x, Int i, bool b) {
    return b ? BIT_SET(x,i) : BIT_CLEAR(x,i);
}

/*constexpr*/ Int BIT_COUNT_LEADING_ZEROS(Int x) {
    if(is_same<Int,i64>::value)
        return x==0 ? 64 : __builtin_clzll(u64(x));
    else if(is_same<Int,i32>::value)
        return x==0 ? 32 : __builtin_clz(u32(x));
    ASSERT(false);
}

/*constexpr*/ Int BIT_COUNT_TRAILING_ZEROS(Int x) {
    if(is_same<Int,i64>::value)
        return x==0 ? 64 : __builtin_ctzll(u64(x));
    else if(is_same<Int,i32>::value)
        return x==0 ? 32 : __builtin_clz(u32(x));
    ASSERT(false);
}

/*constexpr*/ Int BIT_COUNT_ONES(Int x) {
    if(is_same<Int,i64>::value)
        return __builtin_popcountll(u64(x));
    else if(is_same<Int,i32>::value)
        return __builtin_popcount(u32(x));
    ASSERT(false);
}

// 1の個数が奇数なら1, 偶数なら0を返す
/*constexpr*/ Int BIT_PARITY(Int x) {
    if(is_same<Int,i64>::value)
        return __builtin_parityll(u64(x));
    else if(is_same<Int,i32>::value)
        return __builtin_parity(u32(x));
    ASSERT(false);
}

// X ⊆ {0,1,...,n-1}, |X| = k なる部分集合 X を昇順に列挙する
// comb(n,k) 個
//
// ```
// Int x = BIT_I_1(3);
// do {
//     // ...
// } while(BIT_NEXT_SET_SIZED(x, 10));
// ```
constexpr bool BIT_NEXT_SET_SIZED(Int& x, Int n) {
    if(x == 0) return false;
    Int t = (x|(x-1)) + 1;
    x = t | ((~t&(t-1)) >> (BIT_COUNT_TRAILING_ZEROS(x)+1));
    return x < BIT_I(n);
}

// 集合 Y の部分集合 X を昇順に列挙する
// 2^|Y| 個
//
// ```
// Int y = 0b10101;
// Int x = 0;
// do {
//     // ...
// } while(BIT_NEXT_SUBSET(x, y));
// ```
constexpr bool BIT_NEXT_SUBSET(Int& x, Int y) {
    if(x == y) return false;
    x = (x-y) & y;
    return true;
}

// 集合 Y の部分集合 X を降順に列挙する
// 2^|Y| 個
//
// ```
// Int y = 0b10101;
// Int x = y;
// do {
//     // ...
// } while(BIT_PREV_SUBSET(x, y));
// ```
constexpr bool BIT_PREV_SUBSET(Int& x, Int y) {
    if(x == 0) return false;
    x = (x-1) & y;
    return true;
}

// 集合 Y を包含する集合 X ⊆ {0,1,...,n-1} を昇順に列挙する
// 2^(n-|Y|) 個
//
// ```
// Int y = 0b00010101;
// Int x = y;
// do {
//     // ...
// } while(BIT_NEXT_SUPERSET(x, 8, y));
// ```
constexpr bool BIT_NEXT_SUPERSET(Int& x, Int n, Int y) {
    x = (x+1) | y;
    return x < BIT_I(n);
}
// }}}

// lo:OK, hi:NG
template<class Pred>
/*constexpr*/ Int bisect_integer(Int lo, Int hi, Pred pred) {
    ASSERT(lo < hi);

    while(lo+1 < hi) {
        Int mid = (lo+hi) / 2;
        if(pred(mid))
            lo = mid;
        else
            hi = mid;
    }
    return lo;
}

template<class Pred>
/*constexpr*/ Real bisect_real(Real lo, Real hi, Pred pred, Real eps=EPS) {
    ASSERT_LOCAL(!GT_EPS(lo,hi,eps));
    if(lo > hi) swap(lo, hi);

    while(!EQ_EPS(lo,hi,eps)) {
        Real mid = (lo+hi) / 2;
        if(pred(mid))
            lo = mid;
        else
            hi = mid;
    }
    return lo;
}

template<class Monoid>
/*constexpr*/ Monoid fastpow(const Monoid& x, Int e, const Monoid& unity) {
    ASSERT(e >= 0);

    Monoid res = unity;
    Monoid cur = x;
    while(e > 0) {
        if(e & 1)
            res *= cur;
        cur *= cur;
        e >>= 1;
    }
    return res;
}

/*constexpr*/ Int ipow(Int x, Int e) {
    return fastpow<Int>(x,e,1);
}

/*constexpr*/ Int sqrt_floor(Int x) {
    ASSERT(x >= 0);

    Int lo = 0;
    Int hi = MIN(x/2+2, SQRT_MAX<Int>()+1);
    return bisect_integer(lo, hi, [x](Int r) { return r*r <= x; });
}

/*constexpr*/ Int sqrt_ceil(Int x) {
    Int r = sqrt_floor(x);
    return r*r == x ? r : r+1;
}

/*constexpr*/ Int log2_ceil(Int x) {
    ASSERT(x > 0);
    if(is_same<Int,i64>::value)
        return 64 - BIT_COUNT_LEADING_ZEROS(x-1);
    else if(is_same<Int,i32>::value)
        return 32 - BIT_COUNT_LEADING_ZEROS(x-1);
    ASSERT(false);
}

/*constexpr*/ Int log2_floor(Int x) {
    ASSERT(x > 0);
    if(is_same<Int,i64>::value)
        return 63 - BIT_COUNT_LEADING_ZEROS(x);
    else if(is_same<Int,i32>::value)
        return 31 - BIT_COUNT_LEADING_ZEROS(x);
    ASSERT(false);
}

// x > 0
/*constexpr*/ Int pow2_ceil(Int x) {
    return BIT_I(log2_ceil(x));
}

// x > 0
/*constexpr*/ Int pow2_floor(Int x) {
    return BIT_I(log2_floor(x));
}

// Haskell の divMod と同じ
constexpr pair<Int,Int> divmod(Int a, Int b) {
    Int q = a / b;
    Int r = a % b;
    if((b>0 && r<0) || (b<0 && r>0)) {
        --q;
        r += b;
    }
    return {q,r};
}

constexpr Int div_ceil(Int a, Int b) {
    Int q = a / b;
    Int r = a % b;
    if((b>0 && r>0) || (b<0 && r<0))
        ++q;
    return q;
}

constexpr Int div_floor(Int a, Int b) {
    return divmod(a,b).first;
}

constexpr Int modulo(Int a, Int b) {
    return divmod(a,b).second;
}

/*constexpr*/ Int align_ceil(Int x, Int align) {
    ASSERT(align > 0);
    return div_ceil(x,align) * align;
}

/*constexpr*/ Int align_floor(Int x, Int align) {
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

[[noreturn]] void EXIT() {
    cout.flush();
#ifdef PROCON_LOCAL
    cerr.flush();
    exit(0);
#else
    _Exit(0);
#endif
}

// tuple {{{
template<Int I=0, class F, class... TS, SFINAE(sizeof...(TS) == I)>
void tuple_enumerate(tuple<TS...>&, F&&) {}

template<Int I=0, class F, class... TS, SFINAE(sizeof...(TS) > I)>
void tuple_enumerate(tuple<TS...>& t, F&& f) {
    f(I, get<I>(t));
    tuple_enumerate<I+1>(t, forward<F>(f));
}

template<Int I=0, class F, class... TS, SFINAE(sizeof...(TS) == I)>
void tuple_enumerate(const tuple<TS...>&, F&&) {}

template<Int I=0, class F, class... TS, SFINAE(sizeof...(TS) > I)>
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
        tuple_enumerate(t, [&h](Int, const auto& e) {
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
auto vec_make(Int n, T x) {
    return vector<T>(n, x);
}

template<class T, class... Args, SFINAE(sizeof...(Args) >= 2)>
auto vec_make(Int n, Args... args) {
    auto inner = vec_make<T>(args...);
    return vector<decltype(inner)>(n, inner);
}

template<class T>
auto vec_reserve(Int cap) {
    vector<T> res;
    res.reserve(cap);
    return res;
}

template<class T=Int>
auto vec_iota(Int n, T init={}) {
    vector<Int> res(n);
    ALL(iota, res, init);
    return res;
}

template<class ForwardIt, class BinaryOp>
auto vec_scan(ForwardIt first, ForwardIt last,
              typename iterator_traits<ForwardIt>::value_type init,
              BinaryOp op)
{
    using T = typename iterator_traits<ForwardIt>::value_type;
    auto res = vec_reserve<T>(distance(first,last)+1);
    res.emplace_back(init);
    for(; first != last; ++first) {
        init = op(move(init), *first);
        res.emplace_back(init);
    }
    return res;
}

template<class ForwardIt>
auto vec_cum(ForwardIt first, ForwardIt last) {
    using T = typename iterator_traits<ForwardIt>::value_type;
    return vec_scan(first, last, T{}, plus<>{});
}

template<class T, class Comp, class Cont=vector<T>>
auto priority_queue_make(const Comp& comp, Cont&& cont={}) {
    return priority_queue<T,remove_reference_t<Cont>,Comp>(comp, forward<Cont>(cont));
}

template<class T, class Comp>
auto priority_queue_reserve(const Comp& comp, Int cap) {
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
T& array_at(Array<T,N>& ary, Int i) {
    return ary[i];
}

template<class T, size_t N, size_t... NS, class... Args>
T& array_at(Array<T,N,NS...>& ary, Int i, Args... args) {
    return array_at<T,NS...>(ary[i], args...);
}

template<class T, size_t N>
const T& array_at(const Array<T,N>& ary, Int i) {
    return ary[i];
}

template<class T, size_t N, size_t... NS, class... Args>
const T& array_at(const Array<T,N,NS...>& ary, Int i, Args... args) {
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
/*constexpr*/ Int GCD(Int a, Int b) noexcept {
    /*constexpr*/ auto f_gcd = FIX([](auto&& self, Int aa, Int bb) -> Int {
        if(bb == 0) return aa;
        return self(bb, aa%bb);
    });
    return f_gcd(ABS(a), ABS(b));
}

/*constexpr*/ Int LCM(Int a, Int b) noexcept {
    ASSERT(a != 0 && b != 0);
    /*constexpr*/ auto f_gcd = FIX([](auto&& self, Int aa, Int bb) -> Int {
        if(bb == 0) return aa;
        return self(bb, aa%bb);
    });
    a = ABS(a);
    b = ABS(b);
    return a / f_gcd(a,b) * b;
}

/*constexpr*/ tuple<Int,Int,Int> EXTGCD(Int a, Int b) noexcept {
    /*constexpr*/ auto impl = FIX([](auto&& self, Int aa, Int bb, Int& x, Int& y) -> Int {
        if(bb == 0) {
            x = 1; y = 0;
            return aa;
        }
        Int g = self(bb, aa%bb, y, x);
        y -= (aa/bb)*x;
        return g;
    });
    Int x{},y{};
    Int g = impl(ABS(a), ABS(b), x, y);
    x *= SGN(a);
    y *= SGN(b);
    return make_tuple(g, x, y);
}
// }}}

// string {{{
char chr_digit(Int n)  { return char('0'+n); }
Int  ord_digit(char c) { return c-'0'; }
char chr_lower(Int n)  { return char('a'+n); }
Int  ord_lower(char c) { return c-'a'; }
char chr_upper(Int n)  { return char('A'+n); }
Int  ord_upper(char c) { return c-'A'; }

auto str_reserve(Int cap) {
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

template<class T=Int>
T RD() {
    return Scan<T>::scan(cin);
}

template<class T=Int>
T RD1() {
    return Scan1<T>::scan1(cin);
}

template<class T=Int>
auto RD_VEC(Int n) {
    auto res = vec_reserve<T>(n);
    LOOP(n) {
        res.emplace_back(RD<T>());
    }
    return res;
}

template<class T=Int>
auto RD1_VEC(Int n) {
    auto res = vec_reserve<T>(n);
    LOOP(n) {
        res.emplace_back(RD1<T>());
    }
    return res;
}

template<class T=Int>
auto RD_VEC2(Int h, Int w) {
    auto res = vec_reserve<vector<T>>(h);
    LOOP(h) {
        res.emplace_back(RD_VEC<T>(w));
    }
    return res;
}

template<class T=Int>
auto RD1_VEC2(Int h, Int w) {
    auto res = vec_reserve<vector<T>>(h);
    LOOP(h) {
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

template<class T>
string FMT_STR(const T& x) {
    ostringstream out;
    fmt_write(out, x);
    return out.str();
}

template<class... TS>
struct Fmt<tuple<TS...>> {
    static void fmt(ostream& out, const tuple<TS...>& t) {
        tuple_enumerate(t, [&out](Int i, const auto& e) {
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

template<class T>
string DBG_STR(const T& x) {
    ostringstream out;
    dbg_write(out, x);
    return out.str();
}

template<>
struct Dbg<Int> {
    static void dbg(ostream& out, Int x) {
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
        tuple_enumerate(t, [&out](Int i, const auto& e) {
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
void DBG_IMPL(Int line, const char* expr, const T& value) {
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
void DBG_IMPL(Int line, const char* expr, const TS&... value) {
    cerr << "[L " << line << "]: ";
    cerr << "(" << expr << ") = (";
    DBG_IMPL_HELPER(value...);
    cerr << ")\n";
}

template<size_t N, class T, SFINAE(rank<T>::value == 0)>
void DBG_DP_IMPL_HELPER(ostream& out, const T& x, const array<Int,N>&, const array<Int,N>&) {
    dbg_write(out, x);
}

template<size_t N, class T, SFINAE(rank<T>::value > 0)>
void DBG_DP_IMPL_HELPER(ostream& out, const T& x, const array<Int,N>& sizes, const array<Int,N>& offs) {
    Int k   = N - rank<T>::value;
    Int off = offs[k];
    Int siz = sizes[k];
    if(siz == 0) siz = extent<T>::value - off;

    out << "[";
    FOR(i, off, off+siz) {
        if(i != off) out << ",";
        DBG_DP_IMPL_HELPER(out, x[i], sizes, offs);
    }
    out << "]";
}

template<class T, SFINAE(rank<T>::value > 0)>
void DBG_DP_IMPL(Int line, const char* expr, const T& dp,
                 const array<Int,rank<T>::value>& sizes={},
                 const array<Int,rank<T>::value>& offs={})
{
    cerr << "[L " << line << "]: ";
    cerr << expr << " = ";
    DBG_DP_IMPL_HELPER<rank<T>::value>(cerr, dp, sizes, offs);
    cerr << "\n";
}

template<class T>
void DBG_GRID_IMPL(Int line, const char* expr, const vector<T>& grid) {
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
    Int v_;  // [0,Mod::value)

    static Int mod() { return Mod::value; }

    static Int normalize(Int x) {
        Int res = x % mod();
        if(res < 0) res += mod();
        return res;
    }

public:
    ModIntT() : v_(0) {}
    ModIntT(Int v) : v_(normalize(v)) {}

    explicit operator Int() const { return v_; }

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

    ModIntT pow(Int e) const {
        return fastpow(*this, e, ModIntT(1));
    }

    ModIntT inv() const {
        Int g,x; tie(g,x,ignore) = EXTGCD(v_, mod());
        ASSERT(g == 1);
        return ModIntT(x);
    }

    friend ModIntT operator+(ModIntT lhs, ModIntT rhs) { return ModIntT(lhs) += rhs; }
    friend ModIntT operator+(ModIntT lhs, Int rhs)     { return ModIntT(lhs) += rhs; }
    friend ModIntT operator+(Int lhs, ModIntT rhs)     { return ModIntT(rhs) += lhs; }
    friend ModIntT operator-(ModIntT lhs, ModIntT rhs) { return ModIntT(lhs) -= rhs; }
    friend ModIntT operator-(ModIntT lhs, Int rhs)     { return ModIntT(lhs) -= rhs; }
    friend ModIntT operator-(Int lhs, ModIntT rhs)     { return ModIntT(rhs) -= lhs; }
    friend ModIntT operator*(ModIntT lhs, ModIntT rhs) { return ModIntT(lhs) *= rhs; }
    friend ModIntT operator*(ModIntT lhs, Int rhs)     { return ModIntT(lhs) *= rhs; }
    friend ModIntT operator*(Int lhs, ModIntT rhs)     { return ModIntT(rhs) *= lhs; }

    friend bool operator==(ModIntT lhs, ModIntT rhs) { return Int(lhs) == Int(rhs); }
    friend bool operator==(ModIntT lhs, Int rhs)     { return lhs == ModIntT(rhs); }
    friend bool operator==(Int lhs, ModIntT rhs)     { return ModIntT(lhs) == rhs; }
    friend bool operator!=(ModIntT lhs, ModIntT rhs) { return !(lhs == rhs); }
    friend bool operator!=(ModIntT lhs, Int rhs)     { return !(lhs == rhs); }
    friend bool operator!=(Int lhs, ModIntT rhs)     { return !(lhs == rhs); }
};

template<class Mod>
struct ProconHash<ModIntT<Mod>> {
    size_t operator()(ModIntT<Mod> x) const noexcept {
        return procon_hash_value(Int(x));
    }
};

template<class Mod>
struct Scan<ModIntT<Mod>> {
    static ModIntT<Mod> scan(istream& in) {
        Int v = Scan<Int>::scan(in);
        return ModIntT<Mod>(v);
    }
};

template<class Mod>
struct Fmt<ModIntT<Mod>> {
    static void fmt(ostream& out, ModIntT<Mod> x) {
        fmt_write(out, Int(x));
    }
};

template<class Mod>
struct Dbg<ModIntT<Mod>> {
    static void dbg(ostream& out, ModIntT<Mod> x) {
        dbg_write(out, Int(x));
    }
};

template<Int M>
using ModIntC = ModIntT<integral_constant<Int,M>>;

using ModInt = ModIntC<MOD>;
// }}}

// rng {{{
// http://prng.di.unimi.it/xoroshiro128plus.c
struct ProconUrbg {
    using result_type = u64;
    static constexpr result_type min() { return numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return numeric_limits<result_type>::max(); }

    ProconUrbg(u64 s0, u64 s1) : state_{s0,s1} {}

    result_type operator()() {
        u64 s0 = state_[0];
        u64 s1 = state_[1];
        u64 res = s0 + s1;

        s1 ^= s0;
        state_[0] = ((s0<<24)|(s0>>40)) ^ s1 ^ (s1<<16);
        state_[1] = (s1<<37)|(s1>>27);

        return res;
    }

private:
    u64 state_[2];
};

ProconUrbg& PROCON_URBG() {
    static u64 s0 = u64(chrono::system_clock::now().time_since_epoch().count());
    static u64 s1 = u64(&s0);
    static ProconUrbg urbg(s0, s1);
    return urbg;
}
// }}}

// init {{{
struct ProconInit {
    ProconInit() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cin.exceptions(ios::failbit | ios::badbit);
        cout << fixed << setprecision(COUT_PREC);
#ifdef PROCON_LOCAL
        cerr << fixed << setprecision(2);
#endif
        if(COUT_AUTOFLUSH)
            cout << unitbuf;
    }
} PROCON_INIT;
// }}}

// }}}
