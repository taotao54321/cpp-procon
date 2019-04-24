// random {{{

// PCGEngine {{{
// PCG random number generator
//
// http://www.pcg-random.org/
// https://github.com/imneme/pcg-c-basic
class PcgEngine {
public:
    using result_type = std::uint32_t;
    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    PcgEngine(std::uint64_t seed, std::uint64_t seq) {
        init(seed, seq);
    }

    template<typename SeedSeq>
    explicit PcgEngine(SeedSeq& ss) {
        std::uint32_t xs[4];
        ss.generate(std::begin(xs), std::end(xs));
        std::uint64_t seed = (std::uint64_t(xs[0])<<32) | xs[1];
        std::uint64_t seq  = (std::uint64_t(xs[2])<<32) | xs[3];
        init(seed, seq);
    }

    std::uint32_t operator()() {
        std::uint32_t xorshifted = std::uint32_t(((state_>>18) ^ state_) >> 27);
        std::uint32_t rot = std::uint32_t(state_ >> 59);
        std::uint32_t res = (xorshifted>>rot) | (xorshifted<<((-rot)&31));
        state_ = 6364136223846793005ULL*state_ + inc_;
        return res;
    }

private:
    void init(std::uint64_t seed, std::uint64_t seq) {
        state_ = 0;
        inc_ = (seq<<1) | 1;
        (*this)();
        state_ += seed;
        (*this)();
    }

    std::uint64_t state_;
    std::uint64_t inc_;
};
// }}}

// Seeder {{{
class Seeder {
private:
    static constexpr std::uint32_t INIT_A = 0x43b0d7e5;
    static constexpr std::uint32_t MULT_A = 0x931e8875;

    static constexpr std::uint32_t INIT_B = 0x8b51f9dd;
    static constexpr std::uint32_t MULT_B = 0x58f38ded;

    static constexpr std::uint32_t MIX_MULT_L = 0xca01f9dd;
    static constexpr std::uint32_t MIX_MULT_R = 0x4973f715;
    static constexpr std::uint32_t XSHIFT = 16;

    static constexpr std::uint32_t fast_exp(std::uint32_t x, std::uint32_t e) {
        std::uint32_t res = 1;
        std::uint32_t mul = x;
        while(e > 0) {
            if(e & 1)
                res *= mul;
            mul *= mul;
            e >>= 1;
        }
        return res;
    }

    template<typename InputIt>
    void mix_entropy(InputIt first, InputIt last) {
        std::uint32_t hash_const = INIT_A;
        auto h = [&hash_const](std::uint32_t x) {
            x ^= hash_const;
            hash_const *= MULT_A;
            x *= hash_const;
            x ^= x >> XSHIFT;
            return x;
        };
        auto mix = [](std::uint32_t x, std::uint32_t y) {
            std::uint32_t res = MIX_MULT_L*x - MIX_MULT_R*y;
            res ^= res >> XSHIFT;
            return res;
        };

        InputIt it = first;
        for(auto& elem : mixer_)
            elem = h(it == last ? 0 : *it++);
        for(auto& src : mixer_)
            for(auto& dest : mixer_)
                if(&src != &dest)
                    dest = mix(dest, h(src));
        for(; it != last; ++it)
            for(auto& dest : mixer_)
                dest = mix(dest, h(*it));
    }

    std::uint32_t mixer_[4];

public:
    using result_type = std::uint32_t;

    Seeder(const Seeder&)         = delete;
    void operator=(const Seeder&) = delete;

    template<typename InputIt>
    Seeder(InputIt first, InputIt last) {
        seed(first, last);
    }

    template<typename T>
    Seeder(std::initializer_list<T> ilist) : Seeder(begin(ilist),end(ilist)) {}

    template<typename InputIt>
    void seed(InputIt first, InputIt last) {
        mix_entropy(first, last);
    }

    template<typename RandomIt>
    void generate(RandomIt dst_first, RandomIt dst_last) const {
        auto src_first = std::begin(mixer_);
        auto src_last  = std::end(mixer_);
        auto src       = src_first;
        std::uint32_t hash_const = INIT_B;
        for(auto dst = dst_first; dst != dst_last; ++dst) {
            std::uint32_t x = *src++;
            if(src == src_last)
                src = src_first;
            x ^= hash_const;
            hash_const *= MULT_B;
            x *= hash_const;
            x ^= x >> XSHIFT;
            *dst = x;
        }
    }

    std::size_t size() const { return 4; }

    template<typename OutputIt>
    void param(OutputIt first) const {
        constexpr std::uint32_t INV_A     = fast_exp(MULT_A,     std::uint32_t(-1));
        constexpr std::uint32_t MIX_INV_L = fast_exp(MIX_MULT_L, std::uint32_t(-1));

        std::uint32_t res[4];
        std::copy(std::begin(mixer_), std::end(mixer_), std::begin(res));

        std::uint32_t hash_const = INIT_A * fast_exp(MULT_A, 16);
        for(auto src = std::rbegin(res); src != std::rend(res); ++src) {
            for(auto dst = std::rbegin(res); dst != std::rend(res); ++dst) {
                if(src == dst) continue;
                std::uint32_t revhashed = *src;
                std::uint32_t mult_const = hash_const;
                hash_const *= INV_A;
                revhashed ^= hash_const;
                revhashed *= mult_const;
                revhashed ^= revhashed >> XSHIFT;
                std::uint32_t unmixed = *dst;
                unmixed ^= unmixed >> XSHIFT;
                unmixed += MIX_MULT_R*revhashed;
                unmixed *= MIX_INV_L;
                *dst = unmixed;
            }
        }
        for(auto it = std::rbegin(res); it != std::rend(res); ++it) {
            std::uint32_t unhashed = *it;
            unhashed ^= unhashed >> XSHIFT;
            unhashed *= fast_exp(hash_const, std::uint32_t(-1));
            hash_const *= INV_A;
            unhashed ^= hash_const;
            *it = unhashed;
        }

        std::copy(std::begin(res), std::end(res), first);
    }
};
// }}}

// AutoSeeder {{{
#ifndef ENTROPY_CPU
    #if defined(__has_builtin)
        #if __has_builtin(__builtin_readcyclecounter)
            #define ENTROPY_CPU (__builtin_readcyclecounter())
        #endif
    #endif
#endif
#ifndef ENTROPY_CPU
    #if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        #define ENTROPY_CPU (__builtin_ia32_rdtsc())
    #else
        #define ENTROPY_CPU (0)
    #endif
#endif

#ifndef ENTROPY_PID
    #if defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
        #include <unistd.h>
        #define ENTROPY_PID (getpid())
    #else
        #define ENTROPY_PID (0)
    #endif
#endif

template<typename SeedSeq>
class AutoSeederT : public SeedSeq {
private:
    using EntropyArray = std::array<uint32_t,13>;

    template<typename T>
    static std::uint32_t crushto32(T x) {
        if(sizeof(T) <= 4) return std::uint32_t(x);

        std::uint64_t res = std::uint64_t(x);
        res *= 0xbc2ad017d719504d;
        return std::uint32_t(res ^ (res>>32));
    }

    template<typename T>
    static std::uint32_t hash_func(T&& x) {
        return crushto32(std::hash<std::remove_reference_t<std::remove_cv_t<T>>>()(std::forward<T>(x)));
    }

    static constexpr std::uint32_t fnv(std::uint32_t h, const char* pos) {
        if(*pos == '\0') return h;
        return fnv((16777619U*h) ^ *pos, pos+1);
    }

    EntropyArray entropy() const {
        constexpr std::uint32_t compile_stamp = fnv(2166136261U, __DATE__ __TIME__ __FILE__);

        static std::uint32_t random_int = std::random_device()();
        random_int += 0xedf19156;

        auto timestamp = crushto32(std::chrono::high_resolution_clock::now().time_since_epoch().count());

        void* malloc_ptr = malloc(sizeof(int));
        free(malloc_ptr);
        auto addr_heap  = hash_func(malloc_ptr);
        auto addr_stack = hash_func(&malloc_ptr);

        auto addr_this        = hash_func(this);
        auto addr_static_func = hash_func(static_cast<std::uint32_t (*)(std::uint64_t)>(&AutoSeederT::crushto32));

        auto addr_exit_func = hash_func(&_Exit);
        auto addr_time_func = hash_func(&std::chrono::high_resolution_clock::now);

        auto thread_id = hash_func(std::this_thread::get_id());

#if __cpp_rtti || __GXX_RTTI
        auto type_id = crushto32(typeid(*this).hash_code());
#else
        uint32_t type_id = 0;
#endif

        auto cpu = crushto32(ENTROPY_CPU);
        auto pid = crushto32(ENTROPY_PID);

        return {{
            compile_stamp,
            random_int,
            timestamp,
            addr_heap,
            addr_stack,
            addr_this,
            addr_static_func,
            addr_exit_func,
            addr_time_func,
            thread_id,
            type_id,
            cpu,
            pid,
        }};
    }

    AutoSeederT(EntropyArray ea) : SeedSeq(std::begin(ea),std::end(ea)) {}

public:
    AutoSeederT() : AutoSeederT(entropy()) {}

    const SeedSeq& base() const { return *this; }
          SeedSeq& base()       { return *this; }
};

using AutoSeeder = AutoSeederT<Seeder>;
// }}}

// UniformDistributionType {{{
template<typename T>
struct IsUniformInt {
    static constexpr bool value = std::is_same<T,short             >::value ||
                                  std::is_same<T,int               >::value ||
                                  std::is_same<T,long              >::value ||
                                  std::is_same<T,long long         >::value ||
                                  std::is_same<T,unsigned short    >::value ||
                                  std::is_same<T,unsigned int      >::value ||
                                  std::is_same<T,unsigned long     >::value ||
                                  std::is_same<T,unsigned long long>::value;
};

template<typename T>
struct IsUniformReal {
    static constexpr bool value = std::is_same<T,float      >::value ||
                                  std::is_same<T,double     >::value ||
                                  std::is_same<T,long double>::value;
};

template<typename T>
struct IsUniformByte {
    static constexpr bool value = std::is_same<T,char         >::value ||
                                  std::is_same<T,signed char  >::value ||
                                  std::is_same<T,unsigned char>::value;
};

template<typename T, typename Enable=void>
struct UniformDistribution {};

template<typename T>
struct UniformDistribution<T, std::enable_if_t<IsUniformInt<T>::value>> {
    using type = std::uniform_int_distribution<T>;
};

template<typename T>
struct UniformDistribution<T, std::enable_if_t<IsUniformReal<T>::value>> {
    using type = std::uniform_real_distribution<T>;
};

template<typename T>
using UniformDistributionType = typename UniformDistribution<T>::type;

template<typename T, typename Enable=void>
struct UniformDistributionImpl {};

template<typename T>
class UniformDistributionImpl<T, std::enable_if_t<IsUniformByte<T>::value>> {
private:
    using Short = std::conditional_t<std::is_signed<T>::value, short, unsigned short>;
    using Dist  = UniformDistributionType<Short>;

    Dist dist_;

public:
    using result_type = T;
    using param_type  = typename Dist::param_type;

    explicit UniformDistributionImpl(result_type a=0,
                                     result_type b=std::numeric_limits<result_type>::max())
        : dist_(a,b) {}
    explicit UniformDistributionImpl(const param_type& p)
        : dist_(p) {}

    template<typename URNG>
    result_type operator()(URNG& g) {
        return static_cast<result_type>(dist_(g));
    }
    template<typename URNG>
    result_type operator()(URNG& g, const param_type& p) {
        return static_cast<result_type>(dist_(g,p));
    }

    result_type a() const { return static_cast<result_type>(dist_.a()); }
    result_type b() const { return static_cast<result_type>(dist_.b()); }

    param_type param() const { return dist_.param(); }
    void param(const param_type& p) { dist_.param(p); }

    result_type min() const { return a(); }
    result_type max() const { return b(); }

    friend bool operator==(const UniformDistributionImpl& lhs,
                           const UniformDistributionImpl& rhs) {
        return lhs.dist_ == rhs.dist_;
    }
    friend bool operator!=(const UniformDistributionImpl& lhs,
                           const UniformDistributionImpl& rhs) {
        return !(lhs == rhs);
    }
};

template<>
class UniformDistributionImpl<bool> {
private:
    using Dist  = UniformDistributionType<int>;

    Dist dist_;

public:
    using result_type = bool;
    using param_type  = typename Dist::param_type;

    explicit UniformDistributionImpl(result_type a=false, result_type b=true)
        : dist_(a,b) {}
    explicit UniformDistributionImpl(const param_type& p)
        : dist_(p) {}

    template<typename URNG>
    result_type operator()(URNG& g) {
        return static_cast<result_type>(dist_(g));
    }
    template<typename URNG>
    result_type operator()(URNG& g, const param_type& p) {
        return static_cast<result_type>(dist_(g,p));
    }

    result_type a() const { return static_cast<result_type>(dist_.a()); }
    result_type b() const { return static_cast<result_type>(dist_.b()); }

    param_type param() const { return dist_.param(); }
    void param(const param_type& p) { dist_.param(p); }

    result_type min() const { return a(); }
    result_type max() const { return b(); }

    friend bool operator==(const UniformDistributionImpl& lhs,
                           const UniformDistributionImpl& rhs) {
        return lhs.dist_ == rhs.dist_;
    }
    friend bool operator!=(const UniformDistributionImpl& lhs,
                           const UniformDistributionImpl& rhs) {
        return !(lhs == rhs);
    }
};

template<typename T>
struct UniformDistribution<T, std::enable_if_t<IsUniformByte<T>::value>> {
    using type = UniformDistributionImpl<T>;
};
template<>
struct UniformDistribution<bool> {
    using type = UniformDistributionImpl<bool>;
};
// }}}

// Rng {{{
template<typename Engine>
class RngT {
private:
    Engine engine_;

public:
    RngT() : engine_(AutoSeeder().base()) {}
    explicit RngT(std::uint32_t seed) : engine_(Seeder({seed})) {}

    void seed(std::uint32_t seed) { engine_.seed(Seeder({seed})); }

    template<typename R,
             template<typename> class DistT=std::normal_distribution,
             typename... Params>
    R variate(Params&&... params) {
        DistT<R> dist(std::forward<Params>(params)...);
        return dist(engine_);
    }

    template<typename T,
             std::enable_if_t<IsUniformInt<T>::value, std::nullptr_t> = nullptr>
    T uniform(T min_value=std::numeric_limits<T>::min(),
              T max_value=std::numeric_limits<T>::max()) {
        return variate<T,UniformDistributionType>(min_value, max_value);
    }

    template<typename T,
             std::enable_if_t<IsUniformReal<T>::value, std::nullptr_t> = nullptr>
    T uniform(T min_value=-std::numeric_limits<T>::max(),
              T max_value= std::numeric_limits<T>::max()) {
        return variate<T,UniformDistributionType>(min_value, max_value);
    }

    template<typename T,
             std::enable_if_t<IsUniformByte<T>::value, std::nullptr_t> = nullptr>
    T uniform(T min_value=std::numeric_limits<T>::min(),
              T max_value=std::numeric_limits<T>::max()) {
        return variate<T,UniformDistributionType>(min_value, max_value);
    }

    bool uniform() {
        int x = uniform(0, 1);
        return x;
    }

    template<template<typename> class DistT=UniformDistributionType,
             typename OutputIt,
             typename... Params>
    void generate(OutputIt first, OutputIt last, Params&&... params) {
        using R = std::remove_reference_t<decltype(*first)>;
        DistT<R> dist(std::forward<Params>(params)...);
        std::generate(first, last, [this,&dist]() { return dist(engine_); });
    }

    template<typename RandomIt>
    void shuffle(RandomIt first, RandomIt last) {
        std::shuffle(first, last, engine_);
    }

    template<typename ForwardIt>
    ForwardIt choose(ForwardIt first, ForwardIt last) {
        auto d = std::distance(first, last);
        if(d < 2) return first;

        using distance_type = decltype(d);
        distance_type choice = uniform(distance_type(0), --d);
        std::advance(first, choice);
        return first;
    }

    template<typename T>
    auto pick(std::initializer_list<T> ilist) -> decltype(*std::begin(ilist)) {
        return *choose(std::begin(ilist), std::end(ilist));
    }

    template<typename BidiIt>
    BidiIt sample(std::size_t size, BidiIt first, BidiIt last) {
        auto total = std::distance(first, last);
        using distance_type = decltype(total);
        return std::stable_partition(first, last, [this,&size,&total](const auto&) {
            --total;
            if(uniform(distance_type(0),total) < size) {
                --size;
                return true;
            }
            else {
                return false;
            }
        });
    }
};

using Rng = RngT<PcgEngine>;
// }}}

// }}}
