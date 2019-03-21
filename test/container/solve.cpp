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

void test_fmt() {
    {
        deque<i64> deq { 2, 4, 1, 5, 3 };
        assert(TO_STR(deq) == "2 4 1 5 3");
        assert(TO_REPR(deq) == "deque[2, 4, 1, 5, 3]");
    }
}

signed main() {
    test_map();
    test_multiset();

    test_fmt();

    return 0;
}
