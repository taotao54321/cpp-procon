// monoid {{{

template<typename T, typename Op>
struct Monoid {};

template<typename T>
struct Monoid<T,plus<>> {
    static const T UNITY() { return T(0); }
};

template<typename T>
struct Monoid<T,multiplies<>> {
    static const T UNITY() { return T(1); }
};

template<typename T>
struct Monoid<T,OpMax<>> {
    static const T UNITY() { return -PROCON_INF<T>(); }
};

template<typename T>
struct Monoid<T,OpMin<>> {
    static const T UNITY() { return PROCON_INF<T>(); }
};

template<typename T>
struct Monoid<T,OpGcd<>> {
    static const T UNITY() { return T(0); }
};

template<typename T>
struct Monoid<T,OpLcm<>> {
    static const T UNITY() { return T(1); }
};

// }}}
