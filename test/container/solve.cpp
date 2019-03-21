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

void test_pop() {
    {
        vector<i64> v { 5, 3, 4 };
        assert(POP_FRONT(v) == 5);
        assert(POP_BACK(v) == 4);
        assert(POP_BACK(v) == 3);
        assert(v.empty());
    }
    {
        deque<i64> deq { 5, 3, 4 };
        assert(POP_FRONT(deq) == 5);
        assert(POP_BACK(deq) == 4);
        assert(POP_BACK(deq) == 3);
        assert(deq.empty());
    }
    {
        forward_list<i64> ls { 5, 3, 4 };
        assert(POP_FRONT(ls) == 5);
        assert(POP_FRONT(ls) == 3);
        assert(POP_FRONT(ls) == 4);
        assert(ls.empty());
    }
    {
        list<i64> ls { 5, 3, 4 };
        assert(POP_FRONT(ls) == 5);
        assert(POP_BACK(ls) == 4);
        assert(POP_BACK(ls) == 3);
        assert(ls.empty());
    }
    {
        stack<i64> stk;
        stk.emplace(5);
        stk.emplace(3);
        stk.emplace(4);
        assert(POP(stk) == 4);
        assert(POP(stk) == 3);
        assert(POP(stk) == 5);
        assert(stk.empty());
    }
    {
        queue<i64> que;
        que.emplace(5);
        que.emplace(3);
        que.emplace(4);
        assert(POP(que) == 5);
        assert(POP(que) == 3);
        assert(POP(que) == 4);
        assert(que.empty());
    }
    {
        vector<i64> v { 5, 3, 4 };
        MinHeap<i64> que(begin(v), end(v));
        assert(POP(que) == 3);
        assert(POP(que) == 4);
        assert(POP(que) == 5);
        assert(que.empty());
    }
}

void test_fmt() {
    {
        array<i64,5> a { 4, 2, 5, 4, 2 };
        assert(TO_STR(a) == "4 2 5 4 2");
        assert(TO_REPR(a) == "array[4, 2, 5, 4, 2]");
    }
    {
        deque<i64> deq { 2, 4, 1, 5, 3 };
        assert(TO_STR(deq) == "2 4 1 5 3");
        assert(TO_REPR(deq) == "deque[2, 4, 1, 5, 3]");
    }
    {
        forward_list<i64> ls { 2, 4, 1, 5, 3 };
        assert(TO_STR(ls) == "2 4 1 5 3");
        assert(TO_REPR(ls) == "forward_list[2, 4, 1, 5, 3]");
    }
    {
        list<i64> ls { 2, 4, 1, 5, 3 };
        assert(TO_STR(ls) == "2 4 1 5 3");
        assert(TO_REPR(ls) == "list[2, 4, 1, 5, 3]");
    }
    {
        set<i64> s { 2, 4, 1, 5, 3 };
        assert(TO_STR(s) == "1 2 3 4 5");
        assert(TO_REPR(s) == "set[1, 2, 3, 4, 5]");
    }
    {
        multiset<i64> s { 2, 4, 2, 1, 3, 5, 3 };
        assert(TO_STR(s) == "1 2 2 3 3 4 5");
        assert(TO_REPR(s) == "multiset[1, 2, 2, 3, 3, 4, 5]");
    }
    {
        map<i64,i64> m { {4,40}, {2,20}, {3,30}, {1,10} };
        assert(TO_REPR(m) == "map[(1,10), (2,20), (3,30), (4,40)]");
    }
    {
        // キーが等しいものは挿入順に並ぶ
        // 参考: https://en.cppreference.com/w/cpp/container/multimap
        multimap<i64,i64> m { {4,40}, {2,20}, {3,30}, {1,10}, {2,5} };
        assert(TO_REPR(m) == "multimap[(1,10), (2,20), (2,5), (3,30), (4,40)]");
    }
    {
        stack<i64> stk;
        stk.emplace(5);
        stk.emplace(3);
        stk.emplace(4);
        stk.emplace(2);
        stk.emplace(1);
        assert(TO_STR(stk) == "1 2 4 3 5");
        assert(TO_REPR(stk) == "stack[1, 2, 4, 3, 5]");
    }
    {
        queue<i64> que;
        que.emplace(5);
        que.emplace(3);
        que.emplace(4);
        que.emplace(2);
        que.emplace(1);
        assert(TO_STR(que) == "5 3 4 2 1");
        assert(TO_REPR(que) == "queue[5, 3, 4, 2, 1]");
    }
    {
        vector<i64> v { 5, 3, 4, 2, 1 };
        MinHeap<i64> que(begin(v), end(v));
        assert(TO_STR(que) == "1 2 3 4 5");
        assert(TO_REPR(que) == "priority_queue[1, 2, 3, 4, 5]");
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

    test_pop();

    test_fmt();

    EXIT();
}
