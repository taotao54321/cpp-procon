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

template<class T> constexpr T PROCON_INF();
template<> constexpr i32 PROCON_INF<i32>() { return 1'010'000'011; }
template<> constexpr i64 PROCON_INF<i64>() { return INT64_C(1'010'000'000'000'000'017); }
template<> constexpr f32 PROCON_INF<f32>() { return 1e19F; }
template<> constexpr f64 PROCON_INF<f64>() { return 1e100; }
template<> constexpr f80 PROCON_INF<f80>() { return 1e100L; }
