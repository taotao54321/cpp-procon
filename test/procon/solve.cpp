#include "procon.hpp"

void test_bit() {  // {{{
    assert(BIT_GET(0,0) == 0);
    assert(BIT_GET(0,63) == 0);
    assert(BIT_GET(4,2) == 4);
    assert(BIT_GET(4,1) == 0);

    assert(!BIT_TEST(0,0));
    assert(!BIT_TEST(0,63));
    assert( BIT_TEST(4,2));
    assert(!BIT_TEST(4,1));

    assert(BIT_SET(0,0) == 1);
    assert(BIT_SET(1,0) == 1);
    assert(BIT_SET(0,63) == numeric_limits<i64>::min());
    assert(BIT_SET(0b1100,4) == 0b11100);
    assert(BIT_SET(0b1100,3) ==  0b1100);
    assert(BIT_SET(-1,0) == -1);
    assert(BIT_SET(numeric_limits<i64>::max(),63) == -1);

    assert(BIT_CLEAR(0,0) == 0);
    assert(BIT_CLEAR(1,0) == 0);
    assert(BIT_CLEAR(0,63) == 0);
    assert(BIT_CLEAR(0b1100,4) == 0b1100);
    assert(BIT_CLEAR(0b1100,3) == 0b0100);
    assert(BIT_CLEAR(-1,0) == -2);
    assert(BIT_CLEAR(numeric_limits<i64>::max(),62) == (1LL<<62)-1);

    assert(BIT_FLIP(0,0) == 1);
    assert(BIT_FLIP(1,0) == 0);
    assert(BIT_FLIP(0,63) == numeric_limits<i64>::min());
    assert(BIT_FLIP(0b1100,4) == 0b11100);
    assert(BIT_FLIP(0b1100,3) ==  0b0100);
    assert(BIT_FLIP(-1,0) == -2);
    assert(BIT_FLIP(numeric_limits<i64>::max(),63) == -1);

    assert(BIT_ASSIGN(0,0,0) == 0);
    assert(BIT_ASSIGN(0,0,1) == 1);
    assert(BIT_ASSIGN(0,63,1) == numeric_limits<i64>::min());
    assert(BIT_ASSIGN(0b1100,3,1) == 0b1100);
    assert(BIT_ASSIGN(0b1100,3,0) == 0b0100);
    assert(BIT_ASSIGN(-1,0,0) == -2);
    assert(BIT_ASSIGN(numeric_limits<i64>::max(),63,1) == -1);

    assert(BIT_COUNT_LEADING_ZEROS(0) == 64);
    assert(BIT_COUNT_LEADING_ZEROS(1) == 63);
    assert(BIT_COUNT_LEADING_ZEROS(0b1100) == 60);
    assert(BIT_COUNT_LEADING_ZEROS(-1) == 0);
    assert(BIT_COUNT_LEADING_ZEROS((1LL<<62)-1) == 2);

    assert(BIT_COUNT_LEADING_ONES(0) == 0);
    assert(BIT_COUNT_LEADING_ONES(1) == 0);
    assert(BIT_COUNT_LEADING_ONES(-1) == 64);
    assert(BIT_COUNT_LEADING_ONES(-2) == 63);
    assert(BIT_COUNT_LEADING_ONES(-3) == 62);

    assert(BIT_COUNT_TRAILING_ZEROS(0) == 64);
    assert(BIT_COUNT_TRAILING_ZEROS(1) == 0);
    assert(BIT_COUNT_TRAILING_ZEROS(0b1100) == 2);
    assert(BIT_COUNT_TRAILING_ZEROS(-1) == 0);
    assert(BIT_COUNT_TRAILING_ZEROS((1LL<<62)-1) == 0);

    assert(BIT_COUNT_TRAILING_ONES(0) == 0);
    assert(BIT_COUNT_TRAILING_ONES(1) == 1);
    assert(BIT_COUNT_TRAILING_ONES(2) == 0);
    assert(BIT_COUNT_TRAILING_ONES(3) == 2);
    assert(BIT_COUNT_TRAILING_ONES(0b1011) == 2);
    assert(BIT_COUNT_TRAILING_ONES(0b1100) == 0);
    assert(BIT_COUNT_TRAILING_ONES(-1) == 64);
    assert(BIT_COUNT_TRAILING_ONES(-2) == 0);
    assert(BIT_COUNT_TRAILING_ONES((1LL<<62)-1) == 62);

    assert(BIT_MASK_TRAILING_ZEROS(0) == -1);
    assert(BIT_MASK_TRAILING_ZEROS(1) == 0);
    assert(BIT_MASK_TRAILING_ZEROS(2) == 1);
    assert(BIT_MASK_TRAILING_ZEROS(3) == 0);
    assert(BIT_MASK_TRAILING_ZEROS(4) == 3);
    assert(BIT_MASK_TRAILING_ZEROS(0b1011) == 0);
    assert(BIT_MASK_TRAILING_ZEROS(0b1100) == 3);
    assert(BIT_MASK_TRAILING_ZEROS(-1) == 0);
    assert(BIT_MASK_TRAILING_ZEROS(-2) == 1);
    assert(BIT_MASK_TRAILING_ZEROS(1LL<<62) == (1LL<<62)-1);
    assert(BIT_MASK_TRAILING_ZEROS((1LL<<62)-1) == 0);

    assert(BIT_MASK_TRAILING_ONES(0) == 0);
    assert(BIT_MASK_TRAILING_ONES(1) == 1);
    assert(BIT_MASK_TRAILING_ONES(2) == 0);
    assert(BIT_MASK_TRAILING_ONES(3) == 3);
    assert(BIT_MASK_TRAILING_ONES(4) == 0);
    assert(BIT_MASK_TRAILING_ONES(0b1011) == 3);
    assert(BIT_MASK_TRAILING_ONES(0b1100) == 0);
    assert(BIT_MASK_TRAILING_ONES(-1) == -1);
    assert(BIT_MASK_TRAILING_ONES(-2) == 0);
    assert(BIT_MASK_TRAILING_ONES(1LL<<62) == 0);
    assert(BIT_MASK_TRAILING_ONES((1LL<<62)-1) == (1LL<<62)-1);

    assert(BIT_COUNT_ZEROS(0) == 64);
    assert(BIT_COUNT_ZEROS(1) == 63);
    assert(BIT_COUNT_ZEROS(0b1100) == 62);
    assert(BIT_COUNT_ZEROS(-1) == 0);
    assert(BIT_COUNT_ZEROS((1LL<<62)-1) == 2);

    assert(BIT_COUNT_ONES(0) == 0);
    assert(BIT_COUNT_ONES(1) == 1);
    assert(BIT_COUNT_ONES(0b1100) == 2);
    assert(BIT_COUNT_ONES(-1) == 64);
    assert(BIT_COUNT_ONES((1LL<<62)-1) == 62);

    assert(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(0) == 63);
    assert(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(1) == 62);
    assert(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(0b1100) == 59);
    assert(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(-1) == 63);
    assert(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS((1LL<<62)-1) == 1);
    assert(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(-2) == 62);

    assert(BIT_PARITY(0) == 0);
    assert(BIT_PARITY(1) == 1);
    assert(BIT_PARITY(0b1100) == 0);
    assert(BIT_PARITY(-1) == 0);
    assert(BIT_PARITY((1LL<<62)-1) == 0);
    assert(BIT_PARITY((1LL<<61)-1) == 1);

    assert(BIT_EXTRACT_FIRST_ZERO(0) == 1);
    assert(BIT_EXTRACT_FIRST_ZERO(1) == 2);
    assert(BIT_EXTRACT_FIRST_ZERO(2) == 1);
    assert(BIT_EXTRACT_FIRST_ZERO(3) == 4);
    assert(BIT_EXTRACT_FIRST_ZERO(4) == 1);
    assert(BIT_EXTRACT_FIRST_ZERO(6) == 1);
    assert(BIT_EXTRACT_FIRST_ZERO(-1) == 0);
    assert(BIT_EXTRACT_FIRST_ZERO(-2) == 1);

    assert(BIT_EXTRACT_FIRST_ONE(0) == 0);
    assert(BIT_EXTRACT_FIRST_ONE(1) == 1);
    assert(BIT_EXTRACT_FIRST_ONE(2) == 2);
    assert(BIT_EXTRACT_FIRST_ONE(3) == 1);
    assert(BIT_EXTRACT_FIRST_ONE(4) == 4);
    assert(BIT_EXTRACT_FIRST_ONE(6) == 2);
    assert(BIT_EXTRACT_FIRST_ONE(-1) == 1);
    assert(BIT_EXTRACT_FIRST_ONE(-2) == 2);

    assert(BIT_FLIP_FIRST_ZERO(0) == 1);
    assert(BIT_FLIP_FIRST_ZERO(1) == 3);
    assert(BIT_FLIP_FIRST_ZERO(2) == 3);
    assert(BIT_FLIP_FIRST_ZERO(3) == 7);
    assert(BIT_FLIP_FIRST_ZERO(4) == 5);
    assert(BIT_FLIP_FIRST_ZERO(6) == 7);
    assert(BIT_FLIP_FIRST_ZERO(-1) == -1);
    assert(BIT_FLIP_FIRST_ZERO(-2) == -1);

    assert(BIT_FLIP_FIRST_ONE(0) == 0);
    assert(BIT_FLIP_FIRST_ONE(1) == 0);
    assert(BIT_FLIP_FIRST_ONE(2) == 0);
    assert(BIT_FLIP_FIRST_ONE(3) == 2);
    assert(BIT_FLIP_FIRST_ONE(4) == 0);
    assert(BIT_FLIP_FIRST_ONE(6) == 4);
    assert(BIT_FLIP_FIRST_ONE(-1) == -2);
    assert(BIT_FLIP_FIRST_ONE(-2) == -4);

    assert(BIT_FIND_FIRST_ZERO(0) == 1);
    assert(BIT_FIND_FIRST_ZERO(1) == 2);
    assert(BIT_FIND_FIRST_ZERO(0b1100) == 1);
    assert(BIT_FIND_FIRST_ZERO(0b1111) == 5);
    assert(BIT_FIND_FIRST_ZERO(-1) == 0);
    assert(BIT_FIND_FIRST_ZERO((1LL<<62)-1) == 63);

    assert(BIT_FIND_FIRST_ONE(0) == 0);
    assert(BIT_FIND_FIRST_ONE(1) == 1);
    assert(BIT_FIND_FIRST_ONE(0b1100) == 3);
    assert(BIT_FIND_FIRST_ONE(-1) == 1);
    assert(BIT_FIND_FIRST_ONE((1LL<<62)-1) == 1);

    assert(BIT_PROPAGATE_FIRST_ZERO(0) == 0);
    assert(BIT_PROPAGATE_FIRST_ZERO(1) == 0);
    assert(BIT_PROPAGATE_FIRST_ZERO(0b101011) == 0b101000);
    assert(BIT_PROPAGATE_FIRST_ZERO(-1) == -1);
    assert(BIT_PROPAGATE_FIRST_ZERO((1LL<<62)-1) == 0);

    assert(BIT_PROPAGATE_FIRST_ONE(0) == 0);
    assert(BIT_PROPAGATE_FIRST_ONE(1) == 1);
    assert(BIT_PROPAGATE_FIRST_ONE(0b110100) == 0b110111);
    assert(BIT_PROPAGATE_FIRST_ONE(-1) == -1);
    assert(BIT_PROPAGATE_FIRST_ONE(1LL<<62) == numeric_limits<i64>::max());

    assert(BIT_MASKTO_FIRST_ZERO(0) == 1);
    assert(BIT_MASKTO_FIRST_ZERO(1) == 3);
    assert(BIT_MASKTO_FIRST_ZERO(0b101011) == 0b000111);
    assert(BIT_MASKTO_FIRST_ZERO(-1) == 0);
    assert(BIT_MASKTO_FIRST_ZERO((1LL<<62)-1) == numeric_limits<i64>::max());

    assert(BIT_MASKTO_FIRST_ONE(0) == 0);
    assert(BIT_MASKTO_FIRST_ONE(1) == 1);
    assert(BIT_MASKTO_FIRST_ONE(4) == 7);
    assert(BIT_MASKTO_FIRST_ONE(0b110100) == 0b000111);
    assert(BIT_MASKTO_FIRST_ONE(-1) == 1);
    assert(BIT_MASKTO_FIRST_ONE(1LL<<62) == numeric_limits<i64>::max());

    assert(BIT_FLIP_FIRST_ZEROS(0) == -1);
    assert(BIT_FLIP_FIRST_ZEROS(1) == -1);
    assert(BIT_FLIP_FIRST_ZEROS(4) == 7);
    assert(BIT_FLIP_FIRST_ZEROS(0b101001) == 0b101111);
    assert(BIT_FLIP_FIRST_ZEROS(-1) == -1);
    assert(BIT_FLIP_FIRST_ZEROS(1LL<<62) == numeric_limits<i64>::max());
    assert(BIT_FLIP_FIRST_ZEROS((1LL<<62)-1) == -1);

    assert(BIT_FLIP_FIRST_ONES(0) == 0);
    assert(BIT_FLIP_FIRST_ONES(1) == 0);
    assert(BIT_FLIP_FIRST_ONES(4) == 0);
    assert(BIT_FLIP_FIRST_ONES(0b110110) == 0b110000);
    assert(BIT_FLIP_FIRST_ONES(-1) == 0);
    assert(BIT_FLIP_FIRST_ONES(1LL<<50) == 0);
    assert(BIT_FLIP_FIRST_ONES((1LL<<50)-1) == 0);

    {
        i64 x = 0;
        assert(!BIT_NEXT_SET_SIZED(x, 3));

        i64 cnt = 0;
        x = (1LL<<3)-1;
        do {
            ++cnt;
        } while(BIT_NEXT_SET_SIZED(x, 5));
        assert(cnt == 10);
    }
} // }}}

void test_sqrt() {
    assert(sqrt_ceil(0) == 0);
    assert(sqrt_ceil(1) == 1);
    assert(sqrt_ceil(2) == 2);
    assert(sqrt_ceil(3) == 2);
    assert(sqrt_ceil(4) == 2);
    assert(sqrt_ceil(5) == 3);
    assert(sqrt_ceil(99) == 10);
    assert(sqrt_ceil(numeric_limits<i64>::max()) == 3037000500);

    assert(sqrt_floor(0) == 0);
    assert(sqrt_floor(1) == 1);
    assert(sqrt_floor(2) == 1);
    assert(sqrt_floor(3) == 1);
    assert(sqrt_floor(4) == 2);
    assert(sqrt_floor(5) == 2);
    assert(sqrt_floor(99) == 9);
    assert(sqrt_floor(numeric_limits<i64>::max()) == 3037000499);
}

void test_log2() {
    assert(log2_ceil(1) == 0);
    assert(log2_ceil(2) == 1);
    assert(log2_ceil(3) == 2);
    assert(log2_ceil(4) == 2);
    assert(log2_ceil(1LL<<62) == 62);
    assert(log2_ceil((1LL<<62)-1) == 62);
    assert(log2_ceil((1LL<<62)+1) == 63);

    assert(log2_floor(1) == 0);
    assert(log2_floor(2) == 1);
    assert(log2_floor(3) == 1);
    assert(log2_floor(4) == 2);
    assert(log2_floor(1LL<<62) == 62);
    assert(log2_floor((1LL<<62)-1) == 61);
    assert(log2_floor((1LL<<62)+1) == 62);
}

void test_log10() {
    assert(log10_ceil(1) == 0);
    assert(log10_ceil(2) == 1);
    assert(log10_ceil(9) == 1);
    assert(log10_ceil(10) == 1);
    assert(log10_ceil(11) == 2);
    assert(log10_ceil(50) == 2);
    assert(log10_ceil(100) == 2);
    assert(log10_ceil(  999'999'999LL) == 9);
    assert(log10_ceil(1'000'000'000LL) == 9);
    assert(log10_ceil(5'000'000'000LL) == 10);
    assert(log10_ceil(  999'999'999'999'999'999LL) == 18);
    assert(log10_ceil(1'000'000'000'000'000'000LL) == 18);
    assert(log10_ceil(5'000'000'000'000'000'000LL) == 19);

    assert(log10_floor(1) == 0);
    assert(log10_floor(2) == 0);
    assert(log10_floor(9) == 0);
    assert(log10_floor(10) == 1);
    assert(log10_floor(11) == 1);
    assert(log10_floor(50) == 1);
    assert(log10_floor(100) == 2);
    assert(log10_floor(  999'999'999LL) == 8);
    assert(log10_floor(1'000'000'000LL) == 9);
    assert(log10_floor(5'000'000'000LL) == 9);
    assert(log10_floor(  999'999'999'999'999'999LL) == 17);
    assert(log10_floor(1'000'000'000'000'000'000LL) == 18);
    assert(log10_floor(5'000'000'000'000'000'000LL) == 18);
}

void test_pow2() {
    assert( is_mersenne(0));
    assert( is_mersenne(1));
    assert(!is_mersenne(2));
    assert( is_mersenne(3));
    assert(!is_mersenne(4));
    assert(!is_mersenne(5));
    assert(!is_mersenne(13));
    assert(!is_mersenne(1LL<<62));
    assert( is_mersenne((1LL<<62)-1));

    assert( is_pow2(1));
    assert( is_pow2(2));
    assert(!is_pow2(3));
    assert( is_pow2(4));
    assert( is_pow2(1LL<<62));
    assert(!is_pow2((1LL<<62)-1));

    assert(pow2_ceil(1) == 1);
    assert(pow2_ceil(2) == 2);
    assert(pow2_ceil(3) == 4);
    assert(pow2_ceil(4) == 4);
    assert(pow2_ceil(1LL<<62) == (1LL<<62));
    assert(pow2_ceil((1LL<<62)-1) == (1LL<<62));

    assert(pow2_floor(1) == 1);
    assert(pow2_floor(2) == 2);
    assert(pow2_floor(3) == 2);
    assert(pow2_floor(4) == 4);
    assert(pow2_floor(1LL<<62) == (1LL<<62));
    assert(pow2_floor((1LL<<62)-1) == (1LL<<61));
}

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
    test_bit();

    test_sqrt();
    test_log2();
    test_log10();

    test_pow2();

    test_max_min();

    test_fst_snd();

    test_digit_conv();
    test_lower_conv();
    test_upper_conv();

    test_fmt();

    EXIT();
}
