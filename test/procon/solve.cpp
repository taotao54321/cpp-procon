#include "procon.hpp"

void test_max_min() {
    {
        i64 x = 5;
        i64 y = 6;
        assert(MAX(0,x) == x);
        assert(MAX(9,x) == 9);
        assert(MAX(x,y) == y);
        assert(MIN(0,x) == 0);
        assert(MIN(9,x) == x);
        assert(MIN(x,y) == x);
    }
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
        f64 x = 5.0;
        f64 y = 6.0;
        assert(MAX(f32(0),x) == x);
        assert(MAX(f32(9),x) == 9.0);
        assert(MAX(x,y) == y);
        assert(MIN(f32(0),x) == 0.0);
        assert(MIN(f32(9),x) == x);
        assert(MIN(x,y) == x);
#pragma GCC diagnostic pop
    }
    {
        string s("foo");
        string t("bar");
        assert(MAX(s,t) == s);
        assert(MIN(s,t) == t);
    }
    {
        assert(MAX({ 2, 1, 4, 2, 5, 3 }) == 5);
        assert(MIN({ 2, 1, 4, 2, 5, 3 }) == 1);
    }
    {
        string s("foo");
        string t("bar");
        assert(MAX({ s, t }) == s);
        assert(MIN({ s, t }) == t);
    }
    {
        // コンパイルエラー
        //MAX(0, 0.0);
        //MAX(0, 0U);
        //MAX("", 0);
        //MAX(0, string{});
        //MIN(0, 0.0);
        //MIN(0, 0U);
        //MIN("", 0);
        //MIN(0, string{});
    }
}

void test_fst_snd() {
    {
        pair<i64,string> p(5, "foo");
        FST(p) = 3;
        SND(p) = "bar";
        assert(FST(p) == 3);
        assert(SND(p) == "bar");
    }
    {
        tuple<i64,string,char> t(5, "foo", 'z');
        FST(t) = 3;
        SND(t) = "bar";
        assert(FST(t) == 3);
        assert(SND(t) == "bar");
    }
}

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
    test_max_min();

    test_fst_snd();

    test_digit_conv();
    test_lower_conv();
    test_upper_conv();

    test_fmt();

    EXIT();
}
