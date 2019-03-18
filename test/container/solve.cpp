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

void test_multiset() {
    {
        multiset<i64> m { 1, 1, 2, 2, 2, 3 };
        assert(m.count(2) == 3);
        assert(!multiset_erase_one(m, 4));
        assert(multiset_erase_one(m, 2));
        assert(m.count(2) == 2);
        assert(multiset_erase_one(m, 3));
        assert(m.count(3) == 0);
    }

    {
        unordered_multiset<i64> m { 1, 1, 2, 2, 2, 3 };
        assert(m.count(2) == 3);
        assert(!multiset_erase_one(m, 4));
        assert(multiset_erase_one(m, 2));
        assert(m.count(2) == 2);
        assert(multiset_erase_one(m, 3));
        assert(m.count(3) == 0);
    }
}

signed main() {
    test_map();
    test_multiset();

    return 0;
}
