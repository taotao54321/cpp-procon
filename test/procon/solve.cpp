#include "procon.hpp"

void test_digit_conv() {
    string cs("0123456789");
    vector<i64> ds(10);
    ALL(iota, ds, 0);

    {
        string res(10, '\0');
        ALL(transform, ds, begin(res), digit_chr);
        assert(res == cs);
    }
    {
        vector<i64> res(10);
        ALL(transform, cs, begin(res), digit_ord);
        assert(res == ds);
    }
}

void test_lower_conv() {
    string cs(26, '\0');
    ALL(iota, cs, 'a');
    vector<i64> ds(26);
    ALL(iota, ds, 0);

    {
        string res;
        ALL(transform, ds, back_inserter(res), lower_chr);
        assert(res == cs);
    }
    {
        vector<i64> res;
        ALL(transform, cs, back_inserter(res), lower_ord);
    }
}

void test_upper_conv() {
    string cs(26, '\0');
    ALL(iota, cs, 'A');
    vector<i64> ds(26);
    ALL(iota, ds, 0);

    {
        string res;
        ALL(transform, ds, back_inserter(res), upper_chr);
        assert(res == cs);
    }
    {
        vector<i64> res;
        ALL(transform, cs, back_inserter(res), upper_ord);
    }
}

void test_fmt() {
    {
        vector<i64> v { 3, 1, 5, 4, 2 };
        assert(TO_STR(v) == "3 1 5 4 2");
        assert(TO_REPR(v) == "vector[3, 1, 5, 4, 2]");
    }

    {
        assert(TO_STR(make_tuple()) == "");
        assert(TO_REPR(make_tuple()) == "()");
    }

    {
        auto t = make_tuple(1, "foo", make_pair(3,4));
        assert(TO_STR(t) == "1 foo 3 4");
        assert(TO_REPR(t) == "(1,foo,(3,4))");
    }
}

signed main() {
    test_digit_conv();
    test_lower_conv();
    test_upper_conv();

    test_fmt();

    return 0;
}
