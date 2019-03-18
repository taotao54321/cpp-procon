#include "procon.hpp"
#include "container.hpp"

void test_map() {
    {
        map<i64,i64> m;
        assert(!map_contains(m, 5));
        m.emplace(5, 8);
        assert(map_contains(m, 5));
        assert(!map_contains(m, 10));
    }

    {
        unordered_map<i64,i64> m;
        assert(!map_contains(m, 5));
        m.emplace(5, 8);
        assert(map_contains(m, 5));
        assert(!map_contains(m, 10));
    }
}

signed main() {
    test_map();

    return 0;
}
