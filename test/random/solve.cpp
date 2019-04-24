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
    return rng.uniform(numeric_limits<uint32_t>::min(), numeric_limits<uint32_t>::max());
}

int main() {
    test_smallcrush("Seeder", f_seeder);

    test_smallcrush("Rng", f_rng);

    return 0;
}
