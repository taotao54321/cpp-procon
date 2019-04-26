#include <bits/stdc++.h>

extern "C" {
#include <TestU01.h>
}

#include "random.hpp"

using namespace std;

using BitGen = uint32_t (*)();

void test_smallcrush(const string& name, BitGen f) {
    unif01_Gen* gen = unif01_CreateExternGenBits(const_cast<char*>(name.c_str()), f);
    bbattery_SmallCrush(gen);
    unif01_DeleteExternGenBits(gen);
}

uint32_t f_seeder() {
    static uint32_t counter = 0;
    Seeder seeder { counter++, 0U, 0U, 0U };
    uint32_t res;
    seeder.generate(&res, &res+1);
    return res;
}

uint32_t f_rng() {
    static Rng rng;

    static_assert(is_same<int64_t,decltype(rng.uniform(int64_t(0),0))>::value, "");
    static_assert(is_same<unsigned int,decltype(rng.uniform(uint16_t(0),0U))>::value, "");
    static_assert(is_same<double,decltype(rng.uniform(float(0),0.0))>::value, "");

#if 1
    return rng.uniform<uint32_t>();
#else
    uint32_t res = 0;
    for(int i = 0; i < 32; ++i) {
        res <<= 1;
        res  |= rng.uniform<bool>();
    }
    return res;
#endif
}

int main() {
    test_smallcrush("Seeder", f_seeder);

    test_smallcrush("Rng", f_rng);

    return 0;
}
