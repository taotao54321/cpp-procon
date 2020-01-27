#include "procon.hpp"

void test_bit() {  // {{{
    ASSERT(BIT_I(0) == 1);
    ASSERT(BIT_I(1) == 2);
    ASSERT(BIT_I(4) == 16);
    ASSERT(BIT_I(50) == 1LL<<50);

    ASSERT(BIT_I_1(0) == 0);
    ASSERT(BIT_I_1(1) == 1);
    ASSERT(BIT_I_1(4) == 15);
    ASSERT(BIT_I_1(50) == (1LL<<50)-1);

    ASSERT(BIT_GET(0,0) == 0);
    ASSERT(BIT_GET(0,63) == 0);
    ASSERT(BIT_GET(4,2) == 4);
    ASSERT(BIT_GET(4,1) == 0);

    ASSERT(!BIT_TEST(0,0));
    ASSERT(!BIT_TEST(0,63));
    ASSERT( BIT_TEST(4,2));
    ASSERT(!BIT_TEST(4,1));

    ASSERT(BIT_SET(0,0) == 1);
    ASSERT(BIT_SET(1,0) == 1);
    ASSERT(BIT_SET(0,63) == numeric_limits<i64>::min());
    ASSERT(BIT_SET(0b1100,4) == 0b11100);
    ASSERT(BIT_SET(0b1100,3) ==  0b1100);
    ASSERT(BIT_SET(-1,0) == -1);
    ASSERT(BIT_SET(numeric_limits<i64>::max(),63) == -1);

    ASSERT(BIT_CLEAR(0,0) == 0);
    ASSERT(BIT_CLEAR(1,0) == 0);
    ASSERT(BIT_CLEAR(0,63) == 0);
    ASSERT(BIT_CLEAR(0b1100,4) == 0b1100);
    ASSERT(BIT_CLEAR(0b1100,3) == 0b0100);
    ASSERT(BIT_CLEAR(-1,0) == -2);
    ASSERT(BIT_CLEAR(numeric_limits<i64>::max(),62) == (1LL<<62)-1);

    ASSERT(BIT_FLIP(0,0) == 1);
    ASSERT(BIT_FLIP(1,0) == 0);
    ASSERT(BIT_FLIP(0,63) == numeric_limits<i64>::min());
    ASSERT(BIT_FLIP(0b1100,4) == 0b11100);
    ASSERT(BIT_FLIP(0b1100,3) ==  0b0100);
    ASSERT(BIT_FLIP(-1,0) == -2);
    ASSERT(BIT_FLIP(numeric_limits<i64>::max(),63) == -1);

    ASSERT(BIT_ASSIGN(0,0,0) == 0);
    ASSERT(BIT_ASSIGN(0,0,1) == 1);
    ASSERT(BIT_ASSIGN(0,63,1) == numeric_limits<i64>::min());
    ASSERT(BIT_ASSIGN(0b1100,3,1) == 0b1100);
    ASSERT(BIT_ASSIGN(0b1100,3,0) == 0b0100);
    ASSERT(BIT_ASSIGN(-1,0,0) == -2);
    ASSERT(BIT_ASSIGN(numeric_limits<i64>::max(),63,1) == -1);

    ASSERT(BIT_COUNT_LEADING_ZEROS(0) == 64);
    ASSERT(BIT_COUNT_LEADING_ZEROS(1) == 63);
    ASSERT(BIT_COUNT_LEADING_ZEROS(0b1100) == 60);
    ASSERT(BIT_COUNT_LEADING_ZEROS(-1) == 0);
    ASSERT(BIT_COUNT_LEADING_ZEROS((1LL<<62)-1) == 2);

    ASSERT(BIT_COUNT_TRAILING_ZEROS(0) == 64);
    ASSERT(BIT_COUNT_TRAILING_ZEROS(1) == 0);
    ASSERT(BIT_COUNT_TRAILING_ZEROS(0b1100) == 2);
    ASSERT(BIT_COUNT_TRAILING_ZEROS(-1) == 0);
    ASSERT(BIT_COUNT_TRAILING_ZEROS((1LL<<62)-1) == 0);

    ASSERT(BIT_COUNT_ONES(0) == 0);
    ASSERT(BIT_COUNT_ONES(1) == 1);
    ASSERT(BIT_COUNT_ONES(0b1100) == 2);
    ASSERT(BIT_COUNT_ONES(-1) == 64);
    ASSERT(BIT_COUNT_ONES((1LL<<62)-1) == 62);

    ASSERT(BIT_PARITY(0) == 0);
    ASSERT(BIT_PARITY(1) == 1);
    ASSERT(BIT_PARITY(0b1100) == 0);
    ASSERT(BIT_PARITY(-1) == 0);
    ASSERT(BIT_PARITY((1LL<<62)-1) == 0);
    ASSERT(BIT_PARITY((1LL<<61)-1) == 1);

    {
        i64 x = 0;
        ASSERT(!BIT_NEXT_SET_SIZED(x, 3));

        i64 cnt = 0;
        x = (1LL<<3)-1;
        do {
            ++cnt;
        } while(BIT_NEXT_SET_SIZED(x, 5));
        ASSERT(cnt == 10);
    }

    {
        i64 y = 0b10101;
        i64 x = 0b00001;
        ASSERT(BIT_NEXT_SUBSET(x, y));
        ASSERT(x == 0b00100);

        i64 cnt = 0;
        x = 0;
        do {
            ++cnt;
        } while(BIT_NEXT_SUBSET(x, y));
        ASSERT(cnt == 8);

        cnt = 0;
        x = y;
        do {
            ++cnt;
        } while(BIT_PREV_SUBSET(x, y));
        ASSERT(cnt == 8);
    }

    {
        i64 n = 8;
        i64 y = 0b10101;
        i64 x = 0b10111;
        ASSERT(BIT_NEXT_SUPERSET(x, n, y));
        ASSERT(x == 0b11101);

        i64 cnt = 0;
        x = y;
        do {
            ++cnt;
        } while(BIT_NEXT_SUPERSET(x, n, y));
        ASSERT(cnt == 32);
    }
} // }}}

void test_sqrt() {
    ASSERT(sqrt_ceil(0) == 0);
    ASSERT(sqrt_ceil(1) == 1);
    ASSERT(sqrt_ceil(2) == 2);
    ASSERT(sqrt_ceil(3) == 2);
    ASSERT(sqrt_ceil(4) == 2);
    ASSERT(sqrt_ceil(5) == 3);
    ASSERT(sqrt_ceil(99) == 10);
    ASSERT(sqrt_ceil(numeric_limits<i64>::max()) == 3037000500);

    ASSERT(sqrt_floor(0) == 0);
    ASSERT(sqrt_floor(1) == 1);
    ASSERT(sqrt_floor(2) == 1);
    ASSERT(sqrt_floor(3) == 1);
    ASSERT(sqrt_floor(4) == 2);
    ASSERT(sqrt_floor(5) == 2);
    ASSERT(sqrt_floor(99) == 9);
    ASSERT(sqrt_floor(numeric_limits<i64>::max()) == 3037000499);
}

void test_log2() {
    ASSERT(log2_ceil(1) == 0);
    ASSERT(log2_ceil(2) == 1);
    ASSERT(log2_ceil(3) == 2);
    ASSERT(log2_ceil(4) == 2);
    ASSERT(log2_ceil(1LL<<62) == 62);
    ASSERT(log2_ceil((1LL<<62)-1) == 62);
    ASSERT(log2_ceil((1LL<<62)+1) == 63);

    ASSERT(log2_floor(1) == 0);
    ASSERT(log2_floor(2) == 1);
    ASSERT(log2_floor(3) == 1);
    ASSERT(log2_floor(4) == 2);
    ASSERT(log2_floor(1LL<<62) == 62);
    ASSERT(log2_floor((1LL<<62)-1) == 61);
    ASSERT(log2_floor((1LL<<62)+1) == 62);
}

void test_pow2() {
    ASSERT(pow2_ceil(1) == 1);
    ASSERT(pow2_ceil(2) == 2);
    ASSERT(pow2_ceil(3) == 4);
    ASSERT(pow2_ceil(4) == 4);
    ASSERT(pow2_ceil(1LL<<62) == (1LL<<62));
    ASSERT(pow2_ceil((1LL<<62)-1) == (1LL<<62));

    ASSERT(pow2_floor(1) == 1);
    ASSERT(pow2_floor(2) == 2);
    ASSERT(pow2_floor(3) == 2);
    ASSERT(pow2_floor(4) == 4);
    ASSERT(pow2_floor(1LL<<62) == (1LL<<62));
    ASSERT(pow2_floor((1LL<<62)-1) == (1LL<<61));
}

void test_align() {
    ASSERT(align_ceil(0,1) == 0);
    ASSERT(align_ceil(1,1) == 1);
    ASSERT(align_ceil(2,1) == 2);
    ASSERT(align_ceil(6,3) == 6);
    ASSERT(align_ceil(9,10) == 10);
    ASSERT(align_ceil(11,10) == 20);
    ASSERT(align_ceil(-1,1) == -1);
    ASSERT(align_ceil(-2,1) == -2);
    ASSERT(align_ceil(-6,3) == -6);
    ASSERT(align_ceil(-9,10) == 0);
    ASSERT(align_ceil(-11,10) == -10);

    ASSERT(align_floor(0,1) == 0);
    ASSERT(align_floor(1,1) == 1);
    ASSERT(align_floor(2,1) == 2);
    ASSERT(align_floor(6,3) == 6);
    ASSERT(align_floor(9,10) == 0);
    ASSERT(align_floor(11,10) == 10);
    ASSERT(align_floor(-1,1) == -1);
    ASSERT(align_floor(-2,1) == -2);
    ASSERT(align_floor(-6,3) == -6);
    ASSERT(align_floor(-9,10) == -10);
    ASSERT(align_floor(-11,10) == -20);
}

void test_max_min() {
    {
        i64 x = 5;
        i64 y = 6;
        ASSERT(MAX(0,x) == x);
        ASSERT(MAX(9,x) == 9);
        ASSERT(MAX(x,y) == y);
        ASSERT(MIN(0,x) == 0);
        ASSERT(MIN(9,x) == x);
        ASSERT(MIN(x,y) == x);
    }
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
        f64 x = 5.0;
        f64 y = 6.0;
        ASSERT(MAX(f32(0),x) == x);
        ASSERT(MAX(f32(9),x) == 9.0);
        ASSERT(MAX(x,y) == y);
        ASSERT(MIN(f32(0),x) == 0.0);
        ASSERT(MIN(f32(9),x) == x);
        ASSERT(MIN(x,y) == x);
#pragma GCC diagnostic pop
    }
    {
        string s("foo");
        string t("bar");
        ASSERT(MAX(s,t) == s);
        ASSERT(MIN(s,t) == t);
    }
    {
        ASSERT(MAX({ 2, 1, 4, 2, 5, 3 }) == 5);
        ASSERT(MIN({ 2, 1, 4, 2, 5, 3 }) == 1);
    }
    {
        string s("foo");
        string t("bar");
        ASSERT(MAX({ s, t }) == s);
        ASSERT(MIN({ s, t }) == t);
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

void test_digit_conv() {
    string cs("0123456789");
    vector<i64> ds(10);
    ALL(iota, ds, 0);

    {
        string res(10, '\0');
        ALL(transform, ds, begin(res), chr_digit);
        ASSERT(res == cs);
    }
    {
        vector<i64> res(10);
        ALL(transform, cs, begin(res), ord_digit);
        ASSERT(res == ds);
    }
}

void test_lower_conv() {
    string cs(26, '\0');
    ALL(iota, cs, 'a');
    vector<i64> ds(26);
    ALL(iota, ds, 0);

    {
        string res;
        ALL(transform, ds, back_inserter(res), chr_lower);
        ASSERT(res == cs);
    }
    {
        vector<i64> res;
        ALL(transform, cs, back_inserter(res), ord_lower);
    }
}

void test_upper_conv() {
    string cs(26, '\0');
    ALL(iota, cs, 'A');
    vector<i64> ds(26);
    ALL(iota, ds, 0);

    {
        string res;
        ALL(transform, ds, back_inserter(res), chr_upper);
        ASSERT(res == cs);
    }
    {
        vector<i64> res;
        ALL(transform, cs, back_inserter(res), ord_upper);
    }
}

void test_fmt() {
    {
        vector<i64> v { 3, 1, 5, 4, 2 };
        ASSERT(FMT_STR(v) == "3 1 5 4 2");
        ASSERT(DBG_STR(v) == "[3,1,5,4,2]");
    }

    {
        ASSERT(FMT_STR(make_tuple()) == "");
        ASSERT(DBG_STR(make_tuple()) == "()");
    }

    {
        auto t = make_tuple(1, "foo", make_pair(3,4));
        ASSERT(FMT_STR(t) == "1 foo 3 4");
        ASSERT(DBG_STR(t) == "(1,foo,(3,4))");
    }
}

signed main() {
    test_bit();

    test_sqrt();
    test_log2();
    test_pow2();
    test_align();

    test_max_min();

    test_digit_conv();
    test_lower_conv();
    test_upper_conv();

    test_fmt();

    EXIT();
}
