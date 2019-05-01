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

using i8   = int8_t;
using u8   = uint8_t;
using i16  = int16_t;
using u16  = uint16_t;
using i32  = int32_t;
using u32  = uint32_t;
using i64  = int64_t;
using u64  = uint64_t;
#ifdef __SIZEOF_INT128__
using i128 = __int128;
using u128 = unsigned __int128;
#endif

using f32  = float;
using f64  = double;
using f80  = __float80;
using f128 = __float128;
// }}}

template<typename T> constexpr T PROCON_INF();
template<> constexpr i64 PROCON_INF<i64>() { return 1'010'000'000'000'000'017LL; }
template<> constexpr f64 PROCON_INF<f64>() { return 1e100; }

constexpr i64 INF  = PROCON_INF<i64>();
constexpr f64 FINF = PROCON_INF<f64>();

constexpr i64 MOD = 1'000'000'007LL;

constexpr f64 EPS = 1e-12;

constexpr f64 PI = 3.14159265358979323846;

// util {{{
#define FOR(i, start, end) for(i64 i = (start), CPP_CAT(i,xxxx_end)=(end); i < CPP_CAT(i,xxxx_end); ++i)
#define REP(i, n) FOR(i, 0, n)

#define ALL(f,c,...) (([&](decltype((c)) cccc) { return (f)(std::begin(cccc), std::end(cccc), ## __VA_ARGS__); })(c))
#define SLICE(f,c,l,r,...) (([&](decltype((c)) cccc, decltype((l)) llll, decltype((r)) rrrr) {\
    auto iiii = llll <= rrrr ? std::begin(cccc)+llll : std::end(cccc);\
    auto jjjj = llll <= rrrr ? std::begin(cccc)+rrrr : std::end(cccc);\
    return (f)(iiii, jjjj, ## __VA_ARGS__);\
})(c,l,r))

#define GENERIC(f) ([](auto&&... args) -> decltype(auto) { return (f)(std::forward<decltype(args)>(args)...); })

// ビット演算 {{{
// 2の補数を仮定
// 引数は [-INF,INF] のみ想定

i64 BIT_GET(i64 x, i64 i) {
    return x & (1LL<<i);
}

bool BIT_TEST(i64 x, i64 i) {
    return BIT_GET(x,i) != 0;
}

i64 BIT_SET(i64 x, i64 i) {
    return x | (1LL<<i);
}

i64 BIT_CLEAR(i64 x, i64 i) {
    return x & ~(1LL<<i);
}

i64 BIT_FLIP(i64 x, i64 i) {
    return x ^ (1LL<<i);
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

// 末尾へ続く0を識別するマスクを返す (ex. 0b10100 -> 0b00011)
// x=0 なら -1 を返す
i64 BIT_MASK_TRAILING_ZEROS(i64 x) {
    return ~x & (x-1);
}

// 末尾へ続く1を識別するマスクを返す (ex. 0b10011 -> 0b00011)
// x=-1 なら -1 を返す
i64 BIT_MASK_TRAILING_ONES(i64 x) {
    return x & ~(x+1);
}

i64 BIT_COUNT_ONES(i64 x) {
    return __builtin_popcountll(x);
}

i64 BIT_COUNT_ZEROS(i64 x) {
    return 64 - BIT_COUNT_ONES(x);
}

i64 BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(i64 x) {
    return __builtin_clrsbll(x);
}

i64 BIT_PARITY(i64 x) {
    return __builtin_parityll(x);
}

// 最右の0を分離する (ex. 0b11001 -> 0b00010)
// x=-1 なら 0 を返す
i64 BIT_EXTRACT_FIRST_ZERO(i64 x) {
    return ~x & (x+1);
}

// 最右の1を分離する (ex. 0b10110 -> 0b00010)
// x=0 なら 0 を返す
i64 BIT_EXTRACT_FIRST_ONE(i64 x) {
    return x & (-x);
}

// 最右の0を1にする (ex. 0b11001 -> 0b11011)
i64 BIT_FLIP_FIRST_ZERO(i64 x) {
    return x | (x+1);
}

// 最右の1を0にする (ex. 0b10110 -> 0b10100)
i64 BIT_FLIP_FIRST_ONE(i64 x) {
    return x & (x-1);
}

// 最右の1の位置(1-based)を得る
// x=0 なら 0 を返す
i64 BIT_FIND_FIRST_ONE(i64 x) {
    return __builtin_ffsll(x);
}

// 最右の0の位置(1-based)を得る
// x=-1 なら 0 を返す
i64 BIT_FIND_FIRST_ZERO(i64 x) {
    return BIT_FIND_FIRST_ONE(~x);
}

// 最右の0をそれより右に伝播する (ex. 0b11011 -> 0b11000)
// x=-1 なら -1 を返す
i64 BIT_PROPAGATE_FIRST_ZERO(i64 x) {
    if(x == -1) return -1;
    return x & (x+1);
}

// 最右の1をそれより右に伝播する (ex. 0b10100 -> 0b10111)
// x=0 なら 0 を返す
i64 BIT_PROPAGATE_FIRST_ONE(i64 x) {
    if(x == 0) return 0;
    return x | (x-1);
}

// 最右の0および末尾へ続く1を識別するマスクを返す (ex. 0b11011 -> 0b00111)
// x=-1 なら 0 を返す
i64 BIT_MASKTO_FIRST_ZERO(i64 x) {
    if(x == -1) return 0;
    return x ^ (x+1);
}

// 最右の1および末尾へ続く0を識別するマスクを返す (ex. 0b10100 -> 0b00111)
// x=0 なら 0 を返す
i64 BIT_MASKTO_FIRST_ONE(i64 x) {
    if(x == 0) return 0;
    return x ^ (x-1);
}

// 最右の連続した0を1にする (ex. 0b101001 -> 0b101111)
// x=-1 なら -1 を返す
i64 BIT_FLIP_FIRST_ZEROS(i64 x) {
    return ((x&(x+1))-1) | x;
}

// 最右の連続した1を0にする (ex. 0b10110 -> 0b10000)
// x=0 なら 0 を返す
i64 BIT_FLIP_FIRST_ONES(i64 x) {
    return ((x|(x-1))+1) & x;
}
// }}}

// BoolArray {{{
class BoolArray {
public:
    using value_type      = bool;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using iterator        = value_type*;
    using const_iterator  = const value_type*;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;

    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    BoolArray() : BoolArray(0) {}
    explicit BoolArray(size_t n) : BoolArray(n,false) {}
    BoolArray(size_t n, bool value) : size_(n), data_(new bool[n]) {
        ALL(fill, *this, value);
    }

    BoolArray(initializer_list<bool> init) : size_(init.size()), data_(new bool[size_]) {
        ALL(copy, init, begin());
    }

    template<typename InputIt>
    BoolArray(InputIt first, InputIt last) {
        deque<bool> tmp(first, last);
        size_ = tmp.size();
        data_ = new bool[size_];
        ALL(copy, tmp, begin());
    }

    BoolArray(const BoolArray& other) : size_(other.size_), data_(new bool[size_]) {
        ALL(copy, other, begin());
    }

    BoolArray(BoolArray&& other) noexcept : size_(other.size_), data_(other.data_) {
        other.data_ = nullptr;
    }

    BoolArray& operator=(const BoolArray& other) {
        if(this == &other) return *this;
        if(!data_ || size_ < other.size_) {
            delete[] data_;
            data_ = new bool[other.size_];
        }
        size_ = other.size_;
        ALL(copy, other, begin());
        return *this;
    }

    BoolArray& operator=(BoolArray&& other) noexcept {
        if(this == &other) return *this;
        size_ = other.size_;
        data_ = other.data_;
        other.data_ = nullptr;
        return *this;
    }

    BoolArray& operator=(initializer_list<bool> init) {
        if(!data_ || size_ < init.size()) {
            delete[] data_;
            data_ = new bool[init.size()];
        }
        size_ = init.size();
        ALL(copy, init, begin());
        return *this;
    }

    void swap(BoolArray& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    ~BoolArray() {
        delete[] data_;
        data_ = nullptr;
    }

    bool      empty()    const noexcept { return size_ == 0; }
    size_type size()     const noexcept { return size_; }
    size_type max_size() const noexcept { return 1'010'000'000; }

    iterator       begin()        noexcept { return data_; }
    const_iterator begin()  const noexcept { return data_; }
    const_iterator cbegin() const noexcept { return data_; }

    iterator       end()        noexcept { return data_+size_; }
    const_iterator end()  const noexcept { return data_+size_; }
    const_iterator cend() const noexcept { return data_+size_; }

    reverse_iterator       rbegin()        noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    reverse_iterator       rend()        noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend()  const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    reference       operator[](size_type pos)       { return data_[pos]; }
    const_reference operator[](size_type pos) const { return data_[pos]; }

    bool*       data()       noexcept { return data_; }
    const bool* data() const noexcept { return data_; }

private:
    size_t size_;
    bool*  data_;
};

void swap(BoolArray& lhs, BoolArray& rhs) noexcept { lhs.swap(rhs); }

bool operator==(const BoolArray& lhs, const BoolArray& rhs) {
    return equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
}
bool operator!=(const BoolArray& lhs, const BoolArray& rhs) { return !(lhs == rhs); }

bool operator<(const BoolArray& lhs, const BoolArray& rhs) {
    return lexicographical_compare(begin(lhs), end(lhs), begin(rhs), end(rhs));
}
bool operator> (const BoolArray& lhs, const BoolArray& rhs) { return rhs < lhs; }
bool operator<=(const BoolArray& lhs, const BoolArray& rhs) { return !(rhs < lhs); }
bool operator>=(const BoolArray& lhs, const BoolArray& rhs) { return !(lhs < rhs); }
// }}}

// 多次元 vector {{{
// 最内周が vector<bool> になるのを避けるための措置
template<typename T>
struct Array1Container {
    using type = vector<T>;
};
template<>
struct Array1Container<bool> {
    using type = BoolArray;
};

// イテレート用
template<typename T>
struct is_arrayn_container {
    static constexpr bool value = false;
};
template<typename T>
struct is_arrayn_container<vector<T>> {
    static constexpr bool value = true;
};
template<>
struct is_arrayn_container<BoolArray> {
    static constexpr bool value = true;
};

template<typename T>
auto arrayn_make(i64 n, T x) {
    using Cont = typename Array1Container<T>::type;
    return Cont(n, x);
}

template<typename T, typename... Args,
         enable_if_t<2 <= sizeof...(Args), nullptr_t> = nullptr>
auto arrayn_make(i64 n, Args... args) {
    auto inner = arrayn_make<T>(args...);
    return vector<decltype(inner)>(n, inner);
}

template<typename T, typename F>
enable_if_t<!is_arrayn_container<T>::value> arrayn_foreach(T& e, F f) {
    f(e);
}

template<typename T, typename F>
enable_if_t<is_arrayn_container<T>::value> arrayn_foreach(T& ary, F f) {
    for(auto& e : ary)
        arrayn_foreach(e, f);
}

template<typename T, typename U>
enable_if_t<is_arrayn_container<T>::value> arrayn_fill(T& ary, const U& x) {
    arrayn_foreach(ary, [&x](auto& e) { e = x; });
}
// }}}

// 多次元生配列 {{{
template<typename T, typename F>
enable_if_t<rank<T>::value==0> CARRAY_FOREACH(T& e, F f) {
    f(e);
}

template<typename Array, typename F>
enable_if_t<rank<Array>::value!=0> CARRAY_FOREACH(Array& ary, F f) {
    for(auto& e : ary)
        CARRAY_FOREACH(e, f);
}

template<typename Array, typename U>
enable_if_t<rank<Array>::value!=0> CARRAY_FILL(Array& ary, const U& v) {
    CARRAY_FOREACH(ary, [&v](auto& e) { e = v; });
}
// }}}

// メモ化ラッパー (8引数まで) {{{
template<i64 N1, typename F>
class Memoized1 {
    static_assert(N1 >= 1, "");
public:
    explicit Memoized1(F&& f) : f_(forward<F>(f)) {}
    decltype(auto) operator()(i64 x1) const {
        using R = decltype(f_(*this,x1));
        static bool done[N1] {};
        static R    memo[N1];
        if(!done[x1]) {
            memo[x1] = f_(*this,x1);
            done[x1] = true;
        }
        return memo[x1];
    }
private:
    const F f_;
};

template<i64 N1, i64 N2, typename F>
class Memoized2 {
    static_assert(N1 >= 1 && N2 >= 1, "");
public:
    explicit Memoized2(F&& f) : f_(forward<F>(f)) {}
    decltype(auto) operator()(i64 x1, i64 x2) const {
        using R = decltype(f_(*this,x1,x2));
        static bool done[N1][N2] {};
        static R    memo[N1][N2];
        if(!done[x1][x2]) {
            memo[x1][x2] = f_(*this,x1,x2);
            done[x1][x2] = true;
        }
        return memo[x1][x2];
    }
private:
    const F f_;
};

template<i64 N1, i64 N2, i64 N3, typename F>
class Memoized3 {
    static_assert(N1 >= 1 && N2 >= 1 && N3 >= 1, "");
public:
    explicit Memoized3(F&& f) : f_(forward<F>(f)) {}
    decltype(auto) operator()(i64 x1, i64 x2, i64 x3) const {
        using R = decltype(f_(*this,x1,x2,x3));
        static bool done[N1][N2][N3] {};
        static R    memo[N1][N2][N3];
        if(!done[x1][x2][x3]) {
            memo[x1][x2][x3] = f_(*this,x1,x2,x3);
            done[x1][x2][x3] = true;
        }
        return memo[x1][x2][x3];
    }
private:
    const F f_;
};

template<i64 N1, i64 N2, i64 N3, i64 N4, typename F>
class Memoized4 {
    static_assert(N1 >= 1 && N2 >= 1 && N3 >= 1 && N4 >= 1, "");
public:
    explicit Memoized4(F&& f) : f_(forward<F>(f)) {}
    decltype(auto) operator()(i64 x1, i64 x2, i64 x3, i64 x4) const {
        using R = decltype(f_(*this,x1,x2,x3,x4));
        static bool done[N1][N2][N3][N4] {};
        static R    memo[N1][N2][N3][N4];
        if(!done[x1][x2][x3][x4]) {
            memo[x1][x2][x3][x4] = f_(*this,x1,x2,x3,x4);
            done[x1][x2][x3][x4] = true;
        }
        return memo[x1][x2][x3][x4];
    }
private:
    const F f_;
};

template<i64 N1, i64 N2, i64 N3, i64 N4, i64 N5, typename F>
class Memoized5 {
    static_assert(N1 >= 1 && N2 >= 1 && N3 >= 1 && N4 >= 1 && N5 >= 1, "");
public:
    explicit Memoized5(F&& f) : f_(forward<F>(f)) {}
    decltype(auto) operator()(i64 x1, i64 x2, i64 x3, i64 x4, i64 x5) const {
        using R = decltype(f_(*this,x1,x2,x3,x4,x5));
        static bool done[N1][N2][N3][N4][N5] {};
        static R    memo[N1][N2][N3][N4][N5];
        if(!done[x1][x2][x3][x4][x5]) {
            memo[x1][x2][x3][x4][x5] = f_(*this,x1,x2,x3,x4,x5);
            done[x1][x2][x3][x4][x5] = true;
        }
        return memo[x1][x2][x3][x4][x5];
    }
private:
    const F f_;
};

template<i64 N1, i64 N2, i64 N3, i64 N4, i64 N5, i64 N6, typename F>
class Memoized6 {
    static_assert(N1 >= 1 && N2 >= 1 && N3 >= 1 && N4 >= 1 && N5 >= 1 && N6 >= 1, "");
public:
    explicit Memoized6(F&& f) : f_(forward<F>(f)) {}
    decltype(auto) operator()(i64 x1, i64 x2, i64 x3, i64 x4, i64 x5, i64 x6) const {
        using R = decltype(f_(*this,x1,x2,x3,x4,x5,x6));
        static bool done[N1][N2][N3][N4][N5][N6] {};
        static R    memo[N1][N2][N3][N4][N5][N6];
        if(!done[x1][x2][x3][x4][x5][x6]) {
            memo[x1][x2][x3][x4][x5][x6] = f_(*this,x1,x2,x3,x4,x5,x6);
            done[x1][x2][x3][x4][x5][x6] = true;
        }
        return memo[x1][x2][x3][x4][x5][x6];
    }
private:
    const F f_;
};

template<i64 N1, i64 N2, i64 N3, i64 N4, i64 N5, i64 N6, i64 N7, typename F>
class Memoized7 {
    static_assert(N1 >= 1 && N2 >= 1 && N3 >= 1 && N4 >= 1 && N5 >= 1 && N6 >= 1 && N7 >= 1, "");
public:
    explicit Memoized7(F&& f) : f_(forward<F>(f)) {}
    decltype(auto) operator()(i64 x1, i64 x2, i64 x3, i64 x4, i64 x5, i64 x6, i64 x7) const {
        using R = decltype(f_(*this,x1,x2,x3,x4,x5,x6,x7));
        static bool done[N1][N2][N3][N4][N5][N6][N7] {};
        static R    memo[N1][N2][N3][N4][N5][N6][N7];
        if(!done[x1][x2][x3][x4][x5][x6][x7]) {
            memo[x1][x2][x3][x4][x5][x6][x7] = f_(*this,x1,x2,x3,x4,x5,x6,x7);
            done[x1][x2][x3][x4][x5][x6][x7] = true;
        }
        return memo[x1][x2][x3][x4][x5][x6][x7];
    }
private:
    const F f_;
};

template<i64 N1, i64 N2, i64 N3, i64 N4, i64 N5, i64 N6, i64 N7, i64 N8, typename F>
class Memoized8 {
    static_assert(N1 >= 1 && N2 >= 1 && N3 >= 1 && N4 >= 1 && N5 >= 1 && N6 >= 1 && N7 >= 1 && N8 >= 1, "");
public:
    explicit Memoized8(F&& f) : f_(forward<F>(f)) {}
    decltype(auto) operator()(i64 x1, i64 x2, i64 x3, i64 x4, i64 x5, i64 x6, i64 x7, i64 x8) const {
        using R = decltype(f_(*this,x1,x2,x3,x4,x5,x6,x7,x8));
        static bool done[N1][N2][N3][N4][N5][N6][N7][N8] {};
        static R    memo[N1][N2][N3][N4][N5][N6][N7][N8];
        if(!done[x1][x2][x3][x4][x5][x6][x7][x8]) {
            memo[x1][x2][x3][x4][x5][x6][x7][x8] = f_(*this,x1,x2,x3,x4,x5,x6,x7,x8);
            done[x1][x2][x3][x4][x5][x6][x7][x8] = true;
        }
        return memo[x1][x2][x3][x4][x5][x6][x7][x8];
    }
private:
    const F f_;
};

template<i64 N1, typename F>
decltype(auto) MEMOIZE(F&& f) {
    return Memoized1<N1,F>(forward<F>(f));
}
template<i64 N1, i64 N2, typename F>
decltype(auto) MEMOIZE(F&& f) {
    return Memoized2<N1,N2,F>(forward<F>(f));
}
template<i64 N1, i64 N2, i64 N3, typename F>
decltype(auto) MEMOIZE(F&& f) {
    return Memoized3<N1,N2,N3,F>(forward<F>(f));
}
template<i64 N1, i64 N2, i64 N3, i64 N4, typename F>
decltype(auto) MEMOIZE(F&& f) {
    return Memoized4<N1,N2,N3,N4,F>(forward<F>(f));
}
template<i64 N1, i64 N2, i64 N3, i64 N4, i64 N5, typename F>
decltype(auto) MEMOIZE(F&& f) {
    return Memoized5<N1,N2,N3,N4,N5,F>(forward<F>(f));
}
template<i64 N1, i64 N2, i64 N3, i64 N4, i64 N5, i64 N6, typename F>
decltype(auto) MEMOIZE(F&& f) {
    return Memoized6<N1,N2,N3,N4,N5,N6,F>(forward<F>(f));
}
template<i64 N1, i64 N2, i64 N3, i64 N4, i64 N5, i64 N6, i64 N7, typename F>
decltype(auto) MEMOIZE(F&& f) {
    return Memoized7<N1,N2,N3,N4,N5,N6,N7,F>(forward<F>(f));
}
template<i64 N1, i64 N2, i64 N3, i64 N4, i64 N5, i64 N6, i64 N7, i64 N8, typename F>
decltype(auto) MEMOIZE(F&& f) {
    return Memoized8<N1,N2,N3,N4,N5,N6,N7,N8,F>(forward<F>(f));
}

// }}}

// lambda で再帰 {{{
template<typename F>
class FixPoint {
public:
    explicit constexpr FixPoint(F&& f) : f_(forward<F>(f)) {}

    template<typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const {
        return f_(*this, forward<Args>(args)...);
    }

private:
    const F f_;
};

template<typename F>
decltype(auto) FIX(F&& f) {
    return FixPoint<F>(forward<F>(f));
}
// }}}

// tuple {{{
template<typename... TS,
         enable_if_t<0 < sizeof...(TS), nullptr_t> = nullptr>
constexpr auto tuple_head(const tuple<TS...>& t) {
    return get<0>(t);
}

template<typename... TS, size_t i, size_t... is>
constexpr auto tuple_tail_helper(const tuple<TS...>& t, index_sequence<i,is...>) {
    return make_tuple(get<is>(t)...);
}

template<typename... TS,
         enable_if_t<1 == sizeof...(TS), nullptr_t> = nullptr>
constexpr auto tuple_tail(const tuple<TS...>&) {
    return make_tuple();
}

template<typename... TS,
         enable_if_t<1 < sizeof...(TS), nullptr_t> = nullptr>
constexpr auto tuple_tail(const tuple<TS...>& t) {
    return tuple_tail_helper(t, make_index_sequence<sizeof...(TS)>());
}
// }}}

// FST/SND {{{
template<typename T1, typename T2>
T1& FST(pair<T1,T2>& p) {
    return p.first;
}

template<typename T1, typename T2>
const T1& FST(const pair<T1,T2>& p) {
    return p.first;
}

template<typename T1, typename T2>
T2& SND(pair<T1,T2>& p) {
    return p.second;
}

template<typename T1, typename T2>
const T2& SND(const pair<T1,T2>& p) {
    return p.second;
}

template<typename... TS, enable_if_t<1 <= sizeof...(TS), nullptr_t> = nullptr>
auto& FST(tuple<TS...>& t) {
    return get<0>(t);
}

template<typename... TS, enable_if_t<1 <= sizeof...(TS), nullptr_t> = nullptr>
const auto& FST(const tuple<TS...>& t) {
    return get<0>(t);
}

template<typename... TS, enable_if_t<2 <= sizeof...(TS), nullptr_t> = nullptr>
auto& SND(tuple<TS...>& t) {
    return get<1>(t);
}

template<typename... TS, enable_if_t<2 <= sizeof...(TS), nullptr_t> = nullptr>
const auto& SND(const tuple<TS...>& t) {
    return get<1>(t);
}
// }}}

template<typename T1, typename T2, typename Comp=less<>,
         enable_if_t<
             is_integral<T1>::value &&
             is_integral<T2>::value &&
             is_signed<T1>::value != is_unsigned<T2>::value,
             nullptr_t
         > = nullptr>
common_type_t<T1,T2> MAX(T1 x, T2 y, Comp comp={}) {
    return max<common_type_t<T1,T2>>(x, y, comp);
}

template<typename T1, typename T2, typename Comp=less<>,
         enable_if_t<
             is_floating_point<T1>::value &&
             is_floating_point<T2>::value,
             nullptr_t
         > = nullptr>
common_type_t<T1,T2> MAX(T1 x, T2 y, Comp comp={}) {
    return max<common_type_t<T1,T2>>(x, y, comp);
}

template<typename T, typename Comp=less<>>
const T& MAX(const T& x, const T& y, Comp comp={}) {
    return max(x, y, comp);
}

template<typename T, typename Comp=less<>>
T MAX(initializer_list<T> ilist, Comp comp={}) {
    return max(ilist, comp);
}

template<typename T1, typename T2, typename Comp=less<>,
         enable_if_t<
             is_integral<T1>::value &&
             is_integral<T2>::value &&
             is_signed<T1>::value != is_unsigned<T2>::value,
             nullptr_t
         > = nullptr>
common_type_t<T1,T2> MIN(T1 x, T2 y, Comp comp={}) {
    return min<common_type_t<T1,T2>>(x, y, comp);
}

template<typename T1, typename T2, typename Comp=less<>,
         enable_if_t<
             is_floating_point<T1>::value &&
             is_floating_point<T2>::value,
             nullptr_t
         > = nullptr>
common_type_t<T1,T2> MIN(T1 x, T2 y, Comp comp={}) {
    return min<common_type_t<T1,T2>>(x, y, comp);
}

template<typename T, typename Comp=less<>>
const T& MIN(const T& x, const T& y, Comp comp={}) {
    return min(x, y, comp);
}

template<typename T, typename Comp=less<>>
T MIN(initializer_list<T> ilist, Comp comp={}) {
    return min(ilist, comp);
}

template<typename T>
T ABS(T x) {
    static_assert(is_signed<T>::value, "ABS(): argument must be signed");
    return x < 0 ? -x : x;
}

template<typename C>
i64 SIZE(const C& c) { return static_cast<i64>(c.size()); }

template<typename T, size_t N>
i64 SIZE(const T (&)[N]) { return static_cast<i64>(N); }

bool is_odd (i64 x) { return x % 2 != 0; }
bool is_even(i64 x) { return x % 2 == 0; }

template<typename T> i64 cmp(T x, T y) { return (y<x) - (x<y); }
template<typename T> i64 sgn(T x) { return cmp(x, T(0)); }

// 事前条件: a >= 0, b >= 0
i64 gcd_impl(i64 a, i64 b) {
    if(b == 0) return a;
    return gcd_impl(b, a%b);
}

// GCD(0,0) = 0
i64 GCD(i64 a, i64 b) {
    return gcd_impl(ABS(a), ABS(b));
}

// LCM(0,x) は未定義
i64 LCM(i64 a, i64 b) {
    assert(a != 0 && b != 0);
    a = ABS(a);
    b = ABS(b);
    return a / gcd_impl(a,b) * b;
}

// lo:OK, hi:NG
template<typename Pred>
i64 bisect_integer(i64 lo, i64 hi, Pred pred) {
    assert(lo < hi);

    while(lo+1 < hi) {
        i64 mid = (lo+hi) / 2;
        if(pred(mid))
            lo = mid;
        else
            hi = mid;
    }
    return lo;
}

template<typename Pred>
f64 bisect_real(f64 lo, f64 hi, Pred pred, i64 iter=100) {
    assert(lo < hi);

    REP(_, iter) {
        f64 mid = (lo+hi) / 2;
        if(pred(mid))
            lo = mid;
        else
            hi = mid;
    }
    return lo;
}

i64 ipow(i64 x, i64 e) {
    assert(e >= 0);
    i64 res = 1;
    REP(_, e) {
        res *= x;
    }
    return res;
}

i64 sqrt_floor(i64 x) {
    assert(x >= 0);

    i64 lo = 0;
    i64 hi = MIN(x/2+2, 3037000500LL);
    return bisect_integer(lo, hi, [x](i64 r) { return r*r <= x; });
}

i64 sqrt_ceil(i64 x) {
    i64 r = sqrt_floor(x);
    return r*r == x ? r : r+1;
}

// 0 <= log2_ceil(x) <= 63
i64 log2_ceil(i64 x) {
    assert(x > 0);
    return 64 - BIT_COUNT_LEADING_ZEROS(x-1);
}

// 0 <= log2_floor(x) <= 62
i64 log2_floor(i64 x) {
    assert(x > 0);
    return 63 - BIT_COUNT_LEADING_ZEROS(x);
}

// 0 <= log10_ceil(x) <= 19
i64 log10_ceil(i64 x) {
    assert(x > 0);
    static constexpr i64 TABLE[19] {
        1LL,
        10LL,
        100LL,
        1000LL,
        10000LL,
        100000LL,
        1000000LL,
        10000000LL,
        100000000LL,
        1000000000LL,
        10000000000LL,
        100000000000LL,
        1000000000000LL,
        10000000000000LL,
        100000000000000LL,
        1000000000000000LL,
        10000000000000000LL,
        100000000000000000LL,
        1000000000000000000LL,
    };
    REP(i, SIZE(TABLE)) {
        if(x <= TABLE[i]) return i;
    }
    return SIZE(TABLE);
}

// 0 <= log10_floor(x) <= 18
i64 log10_floor(i64 x) {
    assert(x > 0);
    static constexpr i64 TABLE[18] {
        9LL,
        99LL,
        999LL,
        9999LL,
        99999LL,
        999999LL,
        9999999LL,
        99999999LL,
        999999999LL,
        9999999999LL,
        99999999999LL,
        999999999999LL,
        9999999999999LL,
        99999999999999LL,
        999999999999999LL,
        9999999999999999LL,
        99999999999999999LL,
        999999999999999999LL,
    };
    REP(i, SIZE(TABLE)) {
        if(x <= TABLE[i]) return i;
    }
    return SIZE(TABLE);
}

// 2^n - 1 の形かどうか
bool is_mersenne(i64 x) {
    assert(x >= 0);
    return (x&(x+1)) == 0;
}

bool is_pow2(i64 x) {
    assert(x > 0);
    return (x&(x-1)) == 0;
}

// x > 0
i64 pow2_ceil(i64 x) {
    return 1LL << log2_ceil(x);
}

// x > 0
i64 pow2_floor(i64 x) {
    return 1LL << log2_floor(x);
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

bool feq(f64 x, f64 y, f64 eps=EPS) {
    return fabs(x-y) < eps;
}

template<typename T, typename U, typename Comp=less<>>
bool chmax(T& xmax, const U& x, Comp comp={}) {
    if(comp(xmax, x)) {
        xmax = x;
        return true;
    }
    return false;
}

template<typename T, typename U, typename Comp=less<>>
bool chmin(T& xmin, const U& x, Comp comp={}) {
    if(comp(x, xmin)) {
        xmin = x;
        return true;
    }
    return false;
}

template<typename Pred>
i64 arg_find(i64 lo, i64 hi, Pred pred) {
    assert(lo < hi);

    FOR(x, lo, hi) {
        if(pred(x)) return x;
    }
    return INF;
}

template<typename F>
i64 arg_max(i64 lo, i64 hi, F f) {
    assert(lo < hi);

    i64 res = lo;
    auto ymax = f(lo);
    FOR(x, lo+1, hi) {
        if(chmax(ymax, f(x)))
            res = x;
    }
    return res;
}

template<typename F>
i64 arg_min(i64 lo, i64 hi, F f) {
    assert(lo < hi);

    i64 res = lo;
    auto ymin = f(lo);
    FOR(x, lo+1, hi) {
        if(chmin(ymin, f(x)))
            res = x;
    }
    return res;
}

template<typename Pred>
i64 arg_find_r(i64 lo, i64 hi, Pred pred) {
    i64 x = arg_find(-hi+1, lo+1, [pred](i64 xx) { return pred(-xx); });
    return x == INF ? INF : -x;
}

template<typename F>
i64 arg_max_r(i64 lo, i64 hi, F f) {
    return -arg_max(-hi+1, lo+1, [f](i64 x) { return f(-x); });
}

template<typename F>
i64 arg_min_r(i64 lo, i64 hi, F f) {
    return -arg_min(-hi+1, lo+1, [f](i64 x) { return f(-x); });
}

template<typename ForwardIt, typename T, typename Comp=less<>>
ForwardIt bsearch_find(ForwardIt first, ForwardIt last, const T& x, Comp comp={}) {
    auto it = lower_bound(first, last, x, comp);
    if(it == last || comp(x,*it)) return last;
    return it;
}

// x 未満の最後の要素
template<typename BidiIt, typename T, typename Comp=less<>>
BidiIt bsearch_lt(BidiIt first, BidiIt last, const T& x, Comp comp={}) {
    auto it = lower_bound(first, last, x, comp);
    if(it == first) return last;
    return prev(it);
}

// x 以下の最後の要素
template<typename BidiIt, typename T, typename Comp=less<>>
BidiIt bsearch_le(BidiIt first, BidiIt last, const T& x, Comp comp={}) {
    auto it = upper_bound(first, last, x, comp);
    if(it == first) return last;
    return prev(it);
}

// x より大きい最初の要素
template<typename BidiIt, typename T, typename Comp=less<>>
BidiIt bsearch_gt(BidiIt first, BidiIt last, const T& x, Comp comp={}) {
    return upper_bound(first, last, x, comp);
}

// x 以上の最初の要素
template<typename BidiIt, typename T, typename Comp=less<>>
BidiIt bsearch_ge(BidiIt first, BidiIt last, const T& x, Comp comp={}) {
    return lower_bound(first, last, x, comp);
}

template<typename InputIt, typename BinaryOp>
auto FOLD(InputIt first, InputIt last,
          typename iterator_traits<InputIt>::value_type init,
          BinaryOp op)
{
    for(; first != last; ++first)
        init = op(move(init), *first);
    return init;
}

template<typename InputIt, typename BinaryOp>
auto FOLD1(InputIt first, InputIt last, BinaryOp op) {
    auto init = *first++;
    return FOLD(first, last, init, op);
}

template<typename InputIt>
auto SUM(InputIt first, InputIt last) {
    using T = typename iterator_traits<InputIt>::value_type;
    return accumulate(first, last, T());
}

template<typename ForwardIt, typename UnaryOperation>
ForwardIt transform_self(ForwardIt first, ForwardIt last, UnaryOperation op) {
    return transform(first, last, first, op);
}

template<typename C>
void UNIQ(C& c) {
    c.erase(ALL(unique,c), end(c));
}

template<typename BinaryFunc>
auto FLIP(BinaryFunc f) {
    return [f](const auto& x, const auto& y) {
        return f(y,x);
    };
}

template<typename BinaryFunc, typename UnaryFunc>
auto ON(BinaryFunc bf, UnaryFunc uf) {
    return [bf,uf](const auto& x, const auto& y) {
        return bf(uf(x), uf(y));
    };
}

template<typename F>
auto LT_ON(F f) { return ON(less<>(), f); }

template<typename F>
auto GT_ON(F f) { return ON(greater<>(), f); }

template<typename F>
auto EQ_ON(F f) { return ON(equal_to<>(), f); }

template<typename F>
auto NE_ON(F f) { return ON(not_equal_to<>(), f); }

template<typename Comp=less<>>
auto EQUIV(Comp comp={}) {
    return [comp](const auto& lhs, const auto& rhs) {
        return !comp(lhs,rhs) && !comp(rhs,lhs);
    };
}

struct IDENTITY {
    using is_transparent = void;
    template<typename T>
    constexpr T&& operator()(T&& x) const noexcept {
        return forward<T>(x);
    }
};

template<typename T=void>
struct OpMax {
    using result_type          = T;
    using first_argument_type  = T;
    using second_argument_type = T;
    T operator()(const T& x, const T& y) const {
        return MAX(x, y);
    }
};

template<>
struct OpMax<void> {
    using is_transparent = void;
    template<typename T1, typename T2>
    auto operator()(T1&& x, T2&& y) const {
        return MAX(forward<T1>(x), forward<T2>(y));
    }
};

template<typename T=void>
struct OpMin {
    using result_type          = T;
    using first_argument_type  = T;
    using second_argument_type = T;
    T operator()(const T& x, const T& y) const {
        return MIN(x, y);
    }
};

template<>
struct OpMin<void> {
    using is_transparent = void;
    template<typename T1, typename T2>
    auto operator()(T1&& x, T2&& y) const {
        return MIN(forward<T1>(x), forward<T2>(y));
    }
};

template<typename T=void>
struct OpGcd {
    using result_type          = T;
    using first_argument_type  = T;
    using second_argument_type = T;
    T operator()(const T& x, const T& y) const {
        return GCD(x, y);
    }
};

template<>
struct OpGcd<void> {
    using is_transparent = void;
    template<typename T1, typename T2>
    auto operator()(T1&& x, T2&& y) const {
        return GCD(forward<T1>(x), forward<T2>(y));
    }
};

template<typename T=void>
struct OpLcm {
    using result_type          = T;
    using first_argument_type  = T;
    using second_argument_type = T;
    T operator()(const T& x, const T& y) const {
        return LCM(x, y);
    }
};

template<>
struct OpLcm<void> {
    using is_transparent = void;
    template<typename T1, typename T2>
    auto operator()(T1&& x, T2&& y) const {
        return LCM(forward<T1>(x), forward<T2>(y));
    }
};

template<typename ForwardIt>
ForwardIt next_bounded(ForwardIt last, ForwardIt it, i64 n=1) {
    auto bound = distance(it, last);
    return next(it, MIN(n, bound));
}

template<typename ForwardIt>
ForwardIt prev_bounded(ForwardIt first, ForwardIt it, i64 n=1) {
    auto bound = distance(first, it);
    return prev(it, MIN(n, bound));
}

template<typename ForwardIt>
void advance_bounded(ForwardIt first, ForwardIt last, ForwardIt& it, i64 n) {
    if(n > 0) {
        auto bound = distance(it, last);
        advance(it, MIN(n, bound));
    }
    else if(n < 0) {
        auto bound = distance(it, first);
        advance(it, MAX(n, bound));
    }
}

char digit_chr(i64 n) {
    return static_cast<char>('0' + n);
}

i64 digit_ord(char c) {
    return c - '0';
}

char lower_chr(i64 n) {
    return static_cast<char>('a' + n);
}

i64 lower_ord(char c) {
    return c - 'a';
}

char upper_chr(i64 n) {
    return static_cast<char>('A' + n);
}

i64 upper_ord(char c) {
    return c - 'A';
}

// 出力は operator<< を直接使わず、このテンプレート経由で行う
// 提出用出力とデバッグ用出力を分けるため
template<typename T, typename Enable=void>
struct Formatter {
    static ostream& write_str(ostream& out, const T& x)  { return out << x; }
    static ostream& write_repr(ostream& out, const T& x) { return out << x; }
};

template<typename T>
ostream& WRITE_STR(ostream& out, const T& x) {
    return Formatter<T>::write_str(out, x);
}

template<typename T>
ostream& WRITE_REPR(ostream& out, const T& x) {
    return Formatter<T>::write_repr(out, x);
}

template<typename InputIt>
ostream& WRITE_JOIN_STR(ostream& out, InputIt first, InputIt last, const string& sep) {
    while(first != last) {
        WRITE_STR(out, *first++);
        if(first != last)
            out << sep;
    }
    return out;
}

template<typename InputIt>
ostream& WRITE_JOIN_REPR(ostream& out, InputIt first, InputIt last, const string& sep) {
    while(first != last) {
        WRITE_REPR(out, *first++);
        if(first != last)
            out << sep;
    }
    return out;
}

template<typename InputIt>
ostream& WRITE_RANGE_STR(ostream& out, InputIt first, InputIt last) {
    return WRITE_JOIN_STR(out, first, last, " ");
}

template<typename InputIt>
ostream& WRITE_RANGE_REPR(ostream& out, InputIt first, InputIt last) {
    out << "[";
    WRITE_JOIN_REPR(out, first, last, ", ");
    out << "]";
    return out;
}

template<typename T>
void FROM_STR(const string& s, T& x) {
    istringstream in(s);
    in >> x;
}

template<typename T>
string TO_STR(const T& x) {
    ostringstream out;
    WRITE_STR(out, x);
    return out.str();
}

template<typename T>
string TO_REPR(const T& x) {
    ostringstream out;
    WRITE_REPR(out, x);
    return out.str();
}

template<typename InputIt>
string RANGE_TO_STR(InputIt first, InputIt last) {
    ostringstream out;
    WRITE_RANGE_STR(out, first, last);
    return out.str();
}

template<typename InputIt>
string RANGE_TO_REPR(InputIt first, InputIt last) {
    ostringstream out;
    WRITE_RANGE_REPR(out, first, last);
    return out.str();
}

template<typename InputIt>
string JOIN(InputIt first, InputIt last, const string& sep) {
    ostringstream out;
    WRITE_JOIN_STR(out, first, last, sep);
    return out.str();
}

template<>
struct Formatter<i64> {
    static ostream& write_str(ostream& out, i64 x) {
        return out << x;
    }
    static ostream& write_repr(ostream& out, i64 x) {
        if(x == INF) return out << "INF";
        if(x == -INF) return out << "-INF";
        return out << x;
    }
};

template<>
struct Formatter<f64> {
    static ostream& write_str(ostream& out, f64 x) {
        return out << x;
    }
    static ostream& write_repr(ostream& out, f64 x) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
        if(x == FINF) return out << "FINF";
        if(x == -FINF) return out << "-FINF";
#pragma GCC diagnostic pop
        return out << x;
    }
};

template<typename Enum>
struct Formatter<Enum, enable_if_t<is_enum<Enum>::value>> {
    static ostream& write_str(ostream& out, Enum x) {
        return WRITE_STR(out, static_cast<underlying_type_t<Enum>>(x));
    }
    static ostream& write_repr(ostream& out, Enum x) {
        return WRITE_REPR(out, static_cast<underlying_type_t<Enum>>(x));
    }
};

template<typename T>
struct Formatter<vector<T>> {
    static ostream& write_str(ostream& out, const vector<T>& v) {
        return WRITE_RANGE_STR(out, begin(v), end(v));
    }
    static ostream& write_repr(ostream& out, const vector<T>& v) {
        out << "vector";
        return WRITE_RANGE_REPR(out, begin(v), end(v));
    }
};

template<>
struct Formatter<BoolArray> {
    static ostream& write_str(ostream& out, const BoolArray& a) {
        return WRITE_RANGE_STR(out, begin(a), end(a));
    }
    static ostream& write_repr(ostream& out, const BoolArray& a) {
        out << "BoolArray";
        return WRITE_RANGE_REPR(out, begin(a), end(a));
    }
};

template<typename T1, typename T2>
struct Formatter<pair<T1,T2>> {
    static ostream& write_str(ostream& out, const pair<T1,T2>& p) {
        WRITE_STR(out, p.first);
        out << ' ';
        WRITE_STR(out, p.second);
        return out;
    }
    static ostream& write_repr(ostream& out, const pair<T1,T2>& p) {
        out << "(";
        WRITE_REPR(out, p.first);
        out << ",";
        WRITE_REPR(out, p.second);
        out << ")";
        return out;
    }
};

template<typename... TS>
struct Formatter<tuple<TS...>> {
    template<size_t I=0, enable_if_t<I == sizeof...(TS), nullptr_t> = nullptr>
    static ostream& write_str_impl(ostream& out, const tuple<TS...>&) {
        return out;
    }
    template<size_t I=0, enable_if_t<I < sizeof...(TS), nullptr_t> = nullptr>
    static ostream& write_str_impl(ostream& out, const tuple<TS...>& t) {
        if(I != 0) out << ' ';
        WRITE_STR(out, get<I>(t));
        return write_str_impl<I+1>(out, t);
    }

    template<size_t I=0, enable_if_t<I == sizeof...(TS), nullptr_t> = nullptr>
    static ostream& write_repr_impl(ostream& out, const tuple<TS...>&) {
        if(sizeof...(TS) == 0) out << "(";
        return out << ")";
    }
    template<size_t I=0, enable_if_t<I < sizeof...(TS), nullptr_t> = nullptr>
    static ostream& write_repr_impl(ostream& out, const tuple<TS...>& t) {
        if(I == 0)
            out << "(";
        else
            out << ",";
        WRITE_REPR(out, get<I>(t));
        return write_repr_impl<I+1>(out, t);
    }

    static ostream& write_str(ostream& out, const tuple<TS...>& t) {
        return write_str_impl(out, t);
    }
    static ostream& write_repr(ostream& out, const tuple<TS...>& t) {
        return write_repr_impl(out, t);
    }
};

template<typename T>
void RD(T& x) {
    cin >> x;
#ifdef PROCON_LOCAL
    assert(cin);
#endif
}

template<typename T>
void RD1(T& x) {
    RD(x);
    --x;
}

template<typename T>
auto RD_ARRAY(i64 n) {
    auto res = arrayn_make<T>(n, T());
    arrayn_foreach(res, [](T& e) { RD(e); });
    return res;
}

template<typename T>
auto RD1_ARRAY(i64 n) {
    auto res = arrayn_make<T>(n, T());
    arrayn_foreach(res, [](T& e) { RD1(e); });
    return res;
}

template<typename T>
auto RD_ARRAY2(i64 h, i64 w) {
    auto res = arrayn_make<T>(h,w, T());
    arrayn_foreach(res, [](T& e) { RD(e); });
    return res;
}

template<typename T>
auto RD1_ARRAY2(i64 h, i64 w) {
    auto res = arrayn_make<T>(h,w, T());
    arrayn_foreach(res, [](T& e) { RD1(e); });
    return res;
}

template<typename T1, typename T2>
pair<T1,T2> RD_PAIR() {
    T1 x; RD(x);
    T2 y; RD(y);
    return { x, y };
}

template<typename T1, typename T2>
pair<T1,T2> RD1_PAIR() {
    T1 x; RD1(x);
    T2 y; RD1(y);
    return { x, y };
}

template<typename... TS,
         enable_if_t<0 == sizeof...(TS), nullptr_t> = nullptr>
auto RD_TUPLE() {
    return make_tuple();
}

template<typename T, typename... TS>
auto RD_TUPLE() {
    T x; RD(x);
    return tuple_cat(make_tuple(x), RD_TUPLE<TS...>());
}

template<typename... TS,
         enable_if_t<0 == sizeof...(TS), nullptr_t> = nullptr>
auto RD1_TUPLE() {
    return make_tuple();
}

template<typename T, typename... TS>
auto RD1_TUPLE() {
    T x; RD1(x);
    return tuple_cat(make_tuple(x), RD_TUPLE<TS...>());
}

void PRINT() {}

template<typename T, typename... TS>
void PRINT(const T& x, const TS& ...args) {
    WRITE_STR(cout, x);
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

[[noreturn]] void EXIT() {
    cout.flush();
#ifdef PROCON_LOCAL
    cerr.flush();
    exit(0);
#else
    _Exit(0);
#endif
}

template<typename... TS, enable_if_t<1 == sizeof...(TS), nullptr_t> = nullptr>
void DBG_IMPL(i64 line, const char* expr, const tuple<TS...>& value) {
#ifdef PROCON_LOCAL
    cerr << "[L " << line << "]: ";
    cerr << expr << " = ";
    WRITE_REPR(cerr, get<0>(value));
    cerr << "\n";
#endif
}

template<typename... TS, enable_if_t<2 <= sizeof...(TS), nullptr_t> = nullptr>
void DBG_IMPL(i64 line, const char* expr, const tuple<TS...>& value) {
#ifdef PROCON_LOCAL
    cerr << "[L " << line << "]: ";
    cerr << "(" << expr << ") = ";
    WRITE_REPR(cerr, value);
    cerr << "\n";
#endif
}

template<typename T, size_t N>
void DBG_CARRAY_IMPL(i64 line, const char* expr, const T (&ary)[N]) {
#ifdef PROCON_LOCAL
    cerr << "[L " << line << "]: ";
    cerr << expr << " = ";
    WRITE_RANGE_REPR(cerr, begin(ary), end(ary));
    cerr << "\n";
#endif
}

template<typename InputIt>
void DBG_RANGE_IMPL(i64 line, const char* expr1, const char* expr2, InputIt first, InputIt last) {
#ifdef PROCON_LOCAL
    cerr << "[L " << line << "]: ";
    cerr << expr1 << "," << expr2 << " = ";
    WRITE_RANGE_REPR(cerr, first, last);
    cerr << "\n";
#endif
}

#define DBG(args...) DBG_IMPL(__LINE__, CPP_STR_I(args), make_tuple(args))
#define DBG_CARRAY(expr) DBG_CARRAY_IMPL(__LINE__, CPP_STR(expr), (expr))
#define DBG_RANGE(first,last) DBG_RANGE_IMPL(__LINE__, CPP_STR(first), CPP_STR(last), (first), (last))

#define PAIR  make_pair
#define TUPLE make_tuple
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
        cerr << fixed << setprecision(IOS_PREC);
#endif
        if(AUTOFLUSH)
            cout << unitbuf;
    }
} PROCON_INIT;
// }}}
