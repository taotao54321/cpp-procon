#include "procon.hpp"
#include "container.hpp"

void test_bool_array() {
    {
        BoolArray a;
        assert(a.empty());
        assert(a.size() == 0);
        assert(a.begin() == a.end());
        assert(a.rbegin() == a.rend());

        a = { true, false, true, false };
        assert( a[0]);
        assert(!a[1]);
        assert( a[2]);
        assert(!a[3]);
        assert(!a.empty());
        assert(a.size() == 4);
        assert(a == (BoolArray { true, false, true, false }));

        BoolArray b;
        swap(a, b);
        assert(a.empty());
        assert( b[0]);
        assert(!b[1]);
        assert( b[2]);
        assert(!b[3]);
    }
    {
        BoolArray a(4, true);
        a[1] = false;
        assert(a == (BoolArray { true, false, true, true }));

        BoolArray b(begin(a)+1, end(a));
        assert(b == (BoolArray { false, true, true }));

        BoolArray c(rbegin(a), rend(a));
        assert(c == (BoolArray { true, true, false, true }));

        BoolArray d(a);
        assert(a == d);
    }
}

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
    {
        BoolArray a { false, true, true, false, false };
        assert(TO_STR(a) == "0 1 1 0 0");
        assert(TO_REPR(a) == "BoolArray[0, 1, 1, 0, 0]");
    }
}

signed main() {
    test_bool_array();

    test_map();
    test_multiset();

    test_fmt();

    return 0;
}
