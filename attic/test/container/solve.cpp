#include "procon.hpp"
#include "container.hpp"

void test_priority_queue() {
    {
        auto que = make_priority_queue<i64>(GT_ON([](i64 x) { return ABS(x-10); }));
        que.emplace(10);
        que.emplace(11);
        que.emplace(8);
        que.emplace(13);
        que.emplace(6);
        ASSERT(POP(que) == 10);
        ASSERT(POP(que) == 11);
        ASSERT(POP(que) == 8);
        ASSERT(POP(que) == 13);
        ASSERT(POP(que) == 6);
    }
    {
        i64 v[] { 6, 8, 10, 11, 13 };
        auto que = make_priority_queue<i64>(begin(v), end(v), LT_ON([](i64 x) { return ABS(x-10); }));
        ASSERT(POP(que) == 6);
        ASSERT(POP(que) == 13);
        ASSERT(POP(que) == 8);
        ASSERT(POP(que) == 11);
        ASSERT(POP(que) == 10);
    }
}

void test_bool_array() {
    {
        BoolArray a;
        ASSERT(a.empty());
        ASSERT(a.size() == 0);
        ASSERT(a.begin() == a.end());
        ASSERT(a.rbegin() == a.rend());

        a = { true, false, true, false };
        ASSERT( a[0]);
        ASSERT(!a[1]);
        ASSERT( a[2]);
        ASSERT(!a[3]);
        ASSERT(!a.empty());
        ASSERT(a.size() == 4);
        ASSERT(a == (BoolArray { true, false, true, false }));

        BoolArray b;
        swap(a, b);
        ASSERT(a.empty());
        ASSERT( b[0]);
        ASSERT(!b[1]);
        ASSERT( b[2]);
        ASSERT(!b[3]);
    }
    {
        BoolArray a(4, true);
        a[1] = false;
        ASSERT(a == (BoolArray { true, false, true, true }));

        BoolArray b(begin(a)+1, end(a));
        ASSERT(b == (BoolArray { false, true, true }));

        BoolArray c(rbegin(a), rend(a));
        ASSERT(c == (BoolArray { true, true, false, true }));

        BoolArray d(a);
        ASSERT(a == d);
    }
}

void test_map() {
    {
        map<i64,i64> m;
        ASSERT(!map_contains(m, 5));
        m.emplace(5, 8);
        ASSERT(map_contains(m, 5));
        ASSERT(!map_contains(m, 10));
    }
    {
        unordered_map<i64,i64> m;
        ASSERT(!map_contains(m, 5));
        m.emplace(5, 8);
        ASSERT(map_contains(m, 5));
        ASSERT(!map_contains(m, 10));
    }
    {
        multimap<i64,i64> m;
        ASSERT(!map_contains(m, 5));
        m.emplace(5, 8);
        ASSERT(map_contains(m, 5));
        ASSERT(!map_contains(m, 10));
    }
    {
        unordered_multimap<i64,i64> m;
        ASSERT(!map_contains(m, 5));
        m.emplace(5, 8);
        ASSERT(map_contains(m, 5));
        ASSERT(!map_contains(m, 10));
    }

    {
        map<i64,i64> m;
        ASSERT(map_get(m,1,-1) == -1);
        ASSERT(SIZE(m) == 0);
        m[1] = 5;
        ASSERT(map_get(m,1,-1) == 5);
        ASSERT(map_get(m,2,-1) == -1);
        ASSERT(SIZE(m) == 1);
    }
    {
        unordered_map<i64,i64> m;
        ASSERT(map_get(m,1,-1) == -1);
        ASSERT(SIZE(m) == 0);
        m[1] = 5;
        ASSERT(map_get(m,1,-1) == 5);
        ASSERT(map_get(m,2,-1) == -1);
        ASSERT(SIZE(m) == 1);
    }

    {
        map<i64,vector<i64>> m;
        map_setdefault(m, 1, {5}).emplace_back(6);
        ASSERT(m.at(1) == vector<i64>{5,6});
        map_setdefault(m, 1, {}).emplace_back(7);
        ASSERT(m.at(1) == vector<i64>{5,6,7});
        map_setdefault(m, 2, {3});
        ASSERT(m.at(2) == vector<i64>{3});
        ASSERT(SIZE(m) == 2);
    }
    {
        unordered_map<i64,vector<i64>> m;
        map_setdefault(m, 1, {5}).emplace_back(6);
        ASSERT(m.at(1) == vector<i64>{5,6});
        map_setdefault(m, 1, {}).emplace_back(7);
        ASSERT(m.at(1) == vector<i64>{5,6,7});
        map_setdefault(m, 2, {3});
        ASSERT(m.at(2) == vector<i64>{3});
        ASSERT(SIZE(m) == 2);
    }

    {
        map<i64,i64> m;
        auto f = []() {
            static i64 x = 0;
            return x++;
        };
        map_setdefault_with(m, 1, f) += 1;
        ASSERT(SIZE(m) == 1);
        ASSERT(m.at(1) == 1);
        map_setdefault_with(m, 1, f) += 1;
        ASSERT(SIZE(m) == 1);
        ASSERT(m.at(1) == 2);
        map_setdefault_with(m, 2, f);
        map_setdefault_with(m, 3, f);
        ASSERT(SIZE(m) == 3);
        ASSERT(m.at(2) == 1);
        ASSERT(m.at(3) == 2);
    }
    {
        unordered_map<i64,i64> m;
        auto f = []() {
            static i64 x = 0;
            return x++;
        };
        map_setdefault_with(m, 1, f) += 1;
        ASSERT(SIZE(m) == 1);
        ASSERT(m.at(1) == 1);
        map_setdefault_with(m, 1, f) += 1;
        ASSERT(SIZE(m) == 1);
        ASSERT(m.at(1) == 2);
        map_setdefault_with(m, 2, f);
        map_setdefault_with(m, 3, f);
        ASSERT(SIZE(m) == 3);
        ASSERT(m.at(2) == 1);
        ASSERT(m.at(3) == 2);
    }
}

void test_multiset() {
    {
        multiset<i64> s { 1, 1, 2, 2, 2, 5, 6, 6 };
        ASSERT(set_search_lt(s,2) == next(begin(s),1));
        ASSERT(set_search_lt(s,3) == next(begin(s),4));
        ASSERT(set_search_le(s,2) == next(begin(s),4));
        ASSERT(set_search_le(s,3) == next(begin(s),4));
        ASSERT(set_search_gt(s,2) == next(begin(s),5));
        ASSERT(set_search_gt(s,3) == next(begin(s),5));
        ASSERT(set_search_ge(s,2) == next(begin(s),2));
        ASSERT(set_search_ge(s,3) == next(begin(s),5));
    }
    {
        multiset<i64> s { 1, 1, 2, 2, 2, 3 };
        ASSERT(s.count(2) == 3);
        ASSERT(!multiset_erase_one(s, 4));
        ASSERT(multiset_erase_one(s, 2));
        ASSERT(s.count(2) == 2);
        ASSERT(multiset_erase_one(s, 3));
        ASSERT(s.count(3) == 0);
    }
    {
        unordered_multiset<i64> s { 1, 1, 2, 2, 2, 3 };
        ASSERT(s.count(2) == 3);
        ASSERT(!multiset_erase_one(s, 4));
        ASSERT(multiset_erase_one(s, 2));
        ASSERT(s.count(2) == 2);
        ASSERT(multiset_erase_one(s, 3));
        ASSERT(s.count(3) == 0);
    }
}

void test_pop() {
    {
        vector<i64> v { 5, 3, 4 };
        ASSERT(POP_FRONT(v) == 5);
        ASSERT(POP_BACK(v) == 4);
        ASSERT(POP_BACK(v) == 3);
        ASSERT(v.empty());
    }
    {
        deque<i64> deq { 5, 3, 4 };
        ASSERT(POP_FRONT(deq) == 5);
        ASSERT(POP_BACK(deq) == 4);
        ASSERT(POP_BACK(deq) == 3);
        ASSERT(deq.empty());
    }
    {
        forward_list<i64> ls { 5, 3, 4 };
        ASSERT(POP_FRONT(ls) == 5);
        ASSERT(POP_FRONT(ls) == 3);
        ASSERT(POP_FRONT(ls) == 4);
        ASSERT(ls.empty());
    }
    {
        list<i64> ls { 5, 3, 4 };
        ASSERT(POP_FRONT(ls) == 5);
        ASSERT(POP_BACK(ls) == 4);
        ASSERT(POP_BACK(ls) == 3);
        ASSERT(ls.empty());
    }
    {
        stack<i64> stk;
        stk.emplace(5);
        stk.emplace(3);
        stk.emplace(4);
        ASSERT(POP(stk) == 4);
        ASSERT(POP(stk) == 3);
        ASSERT(POP(stk) == 5);
        ASSERT(stk.empty());
    }
    {
        queue<i64> que;
        que.emplace(5);
        que.emplace(3);
        que.emplace(4);
        ASSERT(POP(que) == 5);
        ASSERT(POP(que) == 3);
        ASSERT(POP(que) == 4);
        ASSERT(que.empty());
    }
    {
        vector<i64> v { 5, 3, 4 };
        MinHeap<i64> que(begin(v), end(v));
        ASSERT(POP(que) == 3);
        ASSERT(POP(que) == 4);
        ASSERT(POP(que) == 5);
        ASSERT(que.empty());
    }
}

void test_fmt() {
    {
        array<i64,5> a { 4, 2, 5, 4, 2 };
        ASSERT(TO_STR(a) == "4 2 5 4 2");
        ASSERT(TO_REPR(a) == "array[4, 2, 5, 4, 2]");
    }
    {
        deque<i64> deq { 2, 4, 1, 5, 3 };
        ASSERT(TO_STR(deq) == "2 4 1 5 3");
        ASSERT(TO_REPR(deq) == "deque[2, 4, 1, 5, 3]");
    }
    {
        forward_list<i64> ls { 2, 4, 1, 5, 3 };
        ASSERT(TO_STR(ls) == "2 4 1 5 3");
        ASSERT(TO_REPR(ls) == "forward_list[2, 4, 1, 5, 3]");
    }
    {
        list<i64> ls { 2, 4, 1, 5, 3 };
        ASSERT(TO_STR(ls) == "2 4 1 5 3");
        ASSERT(TO_REPR(ls) == "list[2, 4, 1, 5, 3]");
    }
    {
        set<i64> s { 2, 4, 1, 5, 3 };
        ASSERT(TO_STR(s) == "1 2 3 4 5");
        ASSERT(TO_REPR(s) == "set[1, 2, 3, 4, 5]");
    }
    {
        multiset<i64> s { 2, 4, 2, 1, 3, 5, 3 };
        ASSERT(TO_STR(s) == "1 2 2 3 3 4 5");
        ASSERT(TO_REPR(s) == "multiset[1, 2, 2, 3, 3, 4, 5]");
    }
    {
        map<i64,i64> m { {4,40}, {2,20}, {3,30}, {1,10} };
        ASSERT(TO_REPR(m) == "map[(1,10), (2,20), (3,30), (4,40)]");
    }
    {
        // キーが等しいものは挿入順に並ぶ
        // 参考: https://en.cppreference.com/w/cpp/container/multimap
        multimap<i64,i64> m { {4,40}, {2,20}, {3,30}, {1,10}, {2,5} };
        ASSERT(TO_REPR(m) == "multimap[(1,10), (2,20), (2,5), (3,30), (4,40)]");
    }
    {
        stack<i64> stk;
        stk.emplace(5);
        stk.emplace(3);
        stk.emplace(4);
        stk.emplace(2);
        stk.emplace(1);
        ASSERT(TO_STR(stk) == "1 2 4 3 5");
        ASSERT(TO_REPR(stk) == "stack[1, 2, 4, 3, 5]");
    }
    {
        queue<i64> que;
        que.emplace(5);
        que.emplace(3);
        que.emplace(4);
        que.emplace(2);
        que.emplace(1);
        ASSERT(TO_STR(que) == "5 3 4 2 1");
        ASSERT(TO_REPR(que) == "queue[5, 3, 4, 2, 1]");
    }
    {
        vector<i64> v { 5, 3, 4, 2, 1 };
        MinHeap<i64> que(begin(v), end(v));
        ASSERT(TO_STR(que) == "1 2 3 4 5");
        ASSERT(TO_REPR(que) == "priority_queue[1, 2, 3, 4, 5]");
    }
    {
        BoolArray a { false, true, true, false, false };
        ASSERT(TO_STR(a) == "0 1 1 0 0");
        ASSERT(TO_REPR(a) == "BoolArray[0, 1, 1, 0, 0]");
    }
}

signed main() {
    test_priority_queue();

    test_bool_array();
    test_map();
    test_multiset();

    test_pop();

    test_fmt();

    EXIT();
}
