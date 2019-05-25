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

    ASSERT(BIT_COUNT_LEADING_ONES(0) == 0);
    ASSERT(BIT_COUNT_LEADING_ONES(1) == 0);
    ASSERT(BIT_COUNT_LEADING_ONES(-1) == 64);
    ASSERT(BIT_COUNT_LEADING_ONES(-2) == 63);
    ASSERT(BIT_COUNT_LEADING_ONES(-3) == 62);

    ASSERT(BIT_COUNT_TRAILING_ZEROS(0) == 64);
    ASSERT(BIT_COUNT_TRAILING_ZEROS(1) == 0);
    ASSERT(BIT_COUNT_TRAILING_ZEROS(0b1100) == 2);
    ASSERT(BIT_COUNT_TRAILING_ZEROS(-1) == 0);
    ASSERT(BIT_COUNT_TRAILING_ZEROS((1LL<<62)-1) == 0);

    ASSERT(BIT_COUNT_TRAILING_ONES(0) == 0);
    ASSERT(BIT_COUNT_TRAILING_ONES(1) == 1);
    ASSERT(BIT_COUNT_TRAILING_ONES(2) == 0);
    ASSERT(BIT_COUNT_TRAILING_ONES(3) == 2);
    ASSERT(BIT_COUNT_TRAILING_ONES(0b1011) == 2);
    ASSERT(BIT_COUNT_TRAILING_ONES(0b1100) == 0);
    ASSERT(BIT_COUNT_TRAILING_ONES(-1) == 64);
    ASSERT(BIT_COUNT_TRAILING_ONES(-2) == 0);
    ASSERT(BIT_COUNT_TRAILING_ONES((1LL<<62)-1) == 62);

    ASSERT(BIT_MASK_TRAILING_ZEROS(0) == -1);
    ASSERT(BIT_MASK_TRAILING_ZEROS(1) == 0);
    ASSERT(BIT_MASK_TRAILING_ZEROS(2) == 1);
    ASSERT(BIT_MASK_TRAILING_ZEROS(3) == 0);
    ASSERT(BIT_MASK_TRAILING_ZEROS(4) == 3);
    ASSERT(BIT_MASK_TRAILING_ZEROS(0b1011) == 0);
    ASSERT(BIT_MASK_TRAILING_ZEROS(0b1100) == 3);
    ASSERT(BIT_MASK_TRAILING_ZEROS(-1) == 0);
    ASSERT(BIT_MASK_TRAILING_ZEROS(-2) == 1);
    ASSERT(BIT_MASK_TRAILING_ZEROS(1LL<<62) == (1LL<<62)-1);
    ASSERT(BIT_MASK_TRAILING_ZEROS((1LL<<62)-1) == 0);

    ASSERT(BIT_MASK_TRAILING_ONES(0) == 0);
    ASSERT(BIT_MASK_TRAILING_ONES(1) == 1);
    ASSERT(BIT_MASK_TRAILING_ONES(2) == 0);
    ASSERT(BIT_MASK_TRAILING_ONES(3) == 3);
    ASSERT(BIT_MASK_TRAILING_ONES(4) == 0);
    ASSERT(BIT_MASK_TRAILING_ONES(0b1011) == 3);
    ASSERT(BIT_MASK_TRAILING_ONES(0b1100) == 0);
    ASSERT(BIT_MASK_TRAILING_ONES(-1) == -1);
    ASSERT(BIT_MASK_TRAILING_ONES(-2) == 0);
    ASSERT(BIT_MASK_TRAILING_ONES(1LL<<62) == 0);
    ASSERT(BIT_MASK_TRAILING_ONES((1LL<<62)-1) == (1LL<<62)-1);

    ASSERT(BIT_COUNT_ZEROS(0) == 64);
    ASSERT(BIT_COUNT_ZEROS(1) == 63);
    ASSERT(BIT_COUNT_ZEROS(0b1100) == 62);
    ASSERT(BIT_COUNT_ZEROS(-1) == 0);
    ASSERT(BIT_COUNT_ZEROS((1LL<<62)-1) == 2);

    ASSERT(BIT_COUNT_ONES(0) == 0);
    ASSERT(BIT_COUNT_ONES(1) == 1);
    ASSERT(BIT_COUNT_ONES(0b1100) == 2);
    ASSERT(BIT_COUNT_ONES(-1) == 64);
    ASSERT(BIT_COUNT_ONES((1LL<<62)-1) == 62);

    ASSERT(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(0) == 63);
    ASSERT(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(1) == 62);
    ASSERT(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(0b1100) == 59);
    ASSERT(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(-1) == 63);
    ASSERT(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS((1LL<<62)-1) == 1);
    ASSERT(BIT_COUNT_LEADING_REDUNDANT_SIGN_BITS(-2) == 62);

    ASSERT(BIT_PARITY(0) == 0);
    ASSERT(BIT_PARITY(1) == 1);
    ASSERT(BIT_PARITY(0b1100) == 0);
    ASSERT(BIT_PARITY(-1) == 0);
    ASSERT(BIT_PARITY((1LL<<62)-1) == 0);
    ASSERT(BIT_PARITY((1LL<<61)-1) == 1);

    ASSERT(BIT_EXTRACT_FIRST_ZERO(0) == 1);
    ASSERT(BIT_EXTRACT_FIRST_ZERO(1) == 2);
    ASSERT(BIT_EXTRACT_FIRST_ZERO(2) == 1);
    ASSERT(BIT_EXTRACT_FIRST_ZERO(3) == 4);
    ASSERT(BIT_EXTRACT_FIRST_ZERO(4) == 1);
    ASSERT(BIT_EXTRACT_FIRST_ZERO(6) == 1);
    ASSERT(BIT_EXTRACT_FIRST_ZERO(-1) == 0);
    ASSERT(BIT_EXTRACT_FIRST_ZERO(-2) == 1);

    ASSERT(BIT_EXTRACT_FIRST_ONE(0) == 0);
    ASSERT(BIT_EXTRACT_FIRST_ONE(1) == 1);
    ASSERT(BIT_EXTRACT_FIRST_ONE(2) == 2);
    ASSERT(BIT_EXTRACT_FIRST_ONE(3) == 1);
    ASSERT(BIT_EXTRACT_FIRST_ONE(4) == 4);
    ASSERT(BIT_EXTRACT_FIRST_ONE(6) == 2);
    ASSERT(BIT_EXTRACT_FIRST_ONE(-1) == 1);
    ASSERT(BIT_EXTRACT_FIRST_ONE(-2) == 2);

    ASSERT(BIT_FLIP_FIRST_ZERO(0) == 1);
    ASSERT(BIT_FLIP_FIRST_ZERO(1) == 3);
    ASSERT(BIT_FLIP_FIRST_ZERO(2) == 3);
    ASSERT(BIT_FLIP_FIRST_ZERO(3) == 7);
    ASSERT(BIT_FLIP_FIRST_ZERO(4) == 5);
    ASSERT(BIT_FLIP_FIRST_ZERO(6) == 7);
    ASSERT(BIT_FLIP_FIRST_ZERO(-1) == -1);
    ASSERT(BIT_FLIP_FIRST_ZERO(-2) == -1);

    ASSERT(BIT_FLIP_FIRST_ONE(0) == 0);
    ASSERT(BIT_FLIP_FIRST_ONE(1) == 0);
    ASSERT(BIT_FLIP_FIRST_ONE(2) == 0);
    ASSERT(BIT_FLIP_FIRST_ONE(3) == 2);
    ASSERT(BIT_FLIP_FIRST_ONE(4) == 0);
    ASSERT(BIT_FLIP_FIRST_ONE(6) == 4);
    ASSERT(BIT_FLIP_FIRST_ONE(-1) == -2);
    ASSERT(BIT_FLIP_FIRST_ONE(-2) == -4);

    ASSERT(BIT_FIND_FIRST_ZERO(0) == 1);
    ASSERT(BIT_FIND_FIRST_ZERO(1) == 2);
    ASSERT(BIT_FIND_FIRST_ZERO(0b1100) == 1);
    ASSERT(BIT_FIND_FIRST_ZERO(0b1111) == 5);
    ASSERT(BIT_FIND_FIRST_ZERO(-1) == 0);
    ASSERT(BIT_FIND_FIRST_ZERO((1LL<<62)-1) == 63);

    ASSERT(BIT_FIND_FIRST_ONE(0) == 0);
    ASSERT(BIT_FIND_FIRST_ONE(1) == 1);
    ASSERT(BIT_FIND_FIRST_ONE(0b1100) == 3);
    ASSERT(BIT_FIND_FIRST_ONE(-1) == 1);
    ASSERT(BIT_FIND_FIRST_ONE((1LL<<62)-1) == 1);

    ASSERT(BIT_PROPAGATE_FIRST_ZERO(0) == 0);
    ASSERT(BIT_PROPAGATE_FIRST_ZERO(1) == 0);
    ASSERT(BIT_PROPAGATE_FIRST_ZERO(0b101011) == 0b101000);
    ASSERT(BIT_PROPAGATE_FIRST_ZERO(-1) == -1);
    ASSERT(BIT_PROPAGATE_FIRST_ZERO((1LL<<62)-1) == 0);

    ASSERT(BIT_PROPAGATE_FIRST_ONE(0) == 0);
    ASSERT(BIT_PROPAGATE_FIRST_ONE(1) == 1);
    ASSERT(BIT_PROPAGATE_FIRST_ONE(0b110100) == 0b110111);
    ASSERT(BIT_PROPAGATE_FIRST_ONE(-1) == -1);
    ASSERT(BIT_PROPAGATE_FIRST_ONE(1LL<<62) == numeric_limits<i64>::max());

    ASSERT(BIT_MASKTO_FIRST_ZERO(0) == 1);
    ASSERT(BIT_MASKTO_FIRST_ZERO(1) == 3);
    ASSERT(BIT_MASKTO_FIRST_ZERO(0b101011) == 0b000111);
    ASSERT(BIT_MASKTO_FIRST_ZERO(-1) == 0);
    ASSERT(BIT_MASKTO_FIRST_ZERO((1LL<<62)-1) == numeric_limits<i64>::max());

    ASSERT(BIT_MASKTO_FIRST_ONE(0) == 0);
    ASSERT(BIT_MASKTO_FIRST_ONE(1) == 1);
    ASSERT(BIT_MASKTO_FIRST_ONE(4) == 7);
    ASSERT(BIT_MASKTO_FIRST_ONE(0b110100) == 0b000111);
    ASSERT(BIT_MASKTO_FIRST_ONE(-1) == 1);
    ASSERT(BIT_MASKTO_FIRST_ONE(1LL<<62) == numeric_limits<i64>::max());

    ASSERT(BIT_FLIP_FIRST_ZEROS(0) == -1);
    ASSERT(BIT_FLIP_FIRST_ZEROS(1) == -1);
    ASSERT(BIT_FLIP_FIRST_ZEROS(4) == 7);
    ASSERT(BIT_FLIP_FIRST_ZEROS(0b101001) == 0b101111);
    ASSERT(BIT_FLIP_FIRST_ZEROS(-1) == -1);
    ASSERT(BIT_FLIP_FIRST_ZEROS(1LL<<62) == numeric_limits<i64>::max());
    ASSERT(BIT_FLIP_FIRST_ZEROS((1LL<<62)-1) == -1);

    ASSERT(BIT_FLIP_FIRST_ONES(0) == 0);
    ASSERT(BIT_FLIP_FIRST_ONES(1) == 0);
    ASSERT(BIT_FLIP_FIRST_ONES(4) == 0);
    ASSERT(BIT_FLIP_FIRST_ONES(0b110110) == 0b110000);
    ASSERT(BIT_FLIP_FIRST_ONES(-1) == 0);
    ASSERT(BIT_FLIP_FIRST_ONES(1LL<<50) == 0);
    ASSERT(BIT_FLIP_FIRST_ONES((1LL<<50)-1) == 0);

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

void test_log10() {
    ASSERT(log10_ceil(1) == 0);
    ASSERT(log10_ceil(2) == 1);
    ASSERT(log10_ceil(9) == 1);
    ASSERT(log10_ceil(10) == 1);
    ASSERT(log10_ceil(11) == 2);
    ASSERT(log10_ceil(50) == 2);
    ASSERT(log10_ceil(100) == 2);
    ASSERT(log10_ceil(  999'999'999LL) == 9);
    ASSERT(log10_ceil(1'000'000'000LL) == 9);
    ASSERT(log10_ceil(5'000'000'000LL) == 10);
    ASSERT(log10_ceil(  999'999'999'999'999'999LL) == 18);
    ASSERT(log10_ceil(1'000'000'000'000'000'000LL) == 18);
    ASSERT(log10_ceil(5'000'000'000'000'000'000LL) == 19);

    ASSERT(log10_floor(1) == 0);
    ASSERT(log10_floor(2) == 0);
    ASSERT(log10_floor(9) == 0);
    ASSERT(log10_floor(10) == 1);
    ASSERT(log10_floor(11) == 1);
    ASSERT(log10_floor(50) == 1);
    ASSERT(log10_floor(100) == 2);
    ASSERT(log10_floor(  999'999'999LL) == 8);
    ASSERT(log10_floor(1'000'000'000LL) == 9);
    ASSERT(log10_floor(5'000'000'000LL) == 9);
    ASSERT(log10_floor(  999'999'999'999'999'999LL) == 17);
    ASSERT(log10_floor(1'000'000'000'000'000'000LL) == 18);
    ASSERT(log10_floor(5'000'000'000'000'000'000LL) == 18);
}

void test_pow2() {
    ASSERT( is_mersenne(0));
    ASSERT( is_mersenne(1));
    ASSERT(!is_mersenne(2));
    ASSERT( is_mersenne(3));
    ASSERT(!is_mersenne(4));
    ASSERT(!is_mersenne(5));
    ASSERT(!is_mersenne(13));
    ASSERT(!is_mersenne(1LL<<62));
    ASSERT( is_mersenne((1LL<<62)-1));

    ASSERT( is_pow2(1));
    ASSERT( is_pow2(2));
    ASSERT(!is_pow2(3));
    ASSERT( is_pow2(4));
    ASSERT( is_pow2(1LL<<62));
    ASSERT(!is_pow2((1LL<<62)-1));

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

void test_max_min_clamp() {
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
    {
        i64 x = 3;
        ASSERT(CLAMP(x, 0, 5) == 3);
        ASSERT(CLAMP(x, 5, 9) == 5);
        ASSERT(CLAMP(x, 0, 1) == 1);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
        f64 y = 3.0;
        ASSERT(CLAMP(y, 0.0, 5.0) == 3.0);
        ASSERT(CLAMP(y, 5.0, 9.0) == 5.0);
        ASSERT(CLAMP(y, 0.0, 1.0) == 1.0);
#pragma GCC diagnostic pop

        string s("foo");
        ASSERT(CLAMP(s, string("a"), string("z")) == "foo");
        ASSERT(CLAMP(s, string("h"), string("z")) == "h");
        ASSERT(CLAMP(s, string("a"), string("d")) == "d");
    }
}

void test_fst_snd() {
    {
        pair<i64,string> p(5, "foo");
        FST(p) = 3;
        SND(p) = "bar";
        ASSERT(FST(p) == 3);
        ASSERT(SND(p) == "bar");
    }
    {
        tuple<i64,string,char> t(5, "foo", 'z');
        FST(t) = 3;
        SND(t) = "bar";
        ASSERT(FST(t) == 3);
        ASSERT(SND(t) == "bar");
    }
}

void test_digit_conv() {
    string cs("0123456789");
    vector<i64> ds(10);
    ALL(iota, ds, 0);

    {
        string res(10, '\0');
        ALL(transform, ds, begin(res), digit_chr);
        ASSERT(res == cs);
    }
    {
        vector<i64> res(10);
        ALL(transform, cs, begin(res), digit_ord);
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
        ALL(transform, ds, back_inserter(res), lower_chr);
        ASSERT(res == cs);
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
        ASSERT(res == cs);
    }
    {
        vector<i64> res;
        ALL(transform, cs, back_inserter(res), upper_ord);
    }
}

void test_fmt() {
    {
        vector<i64> v { 3, 1, 5, 4, 2 };
        ASSERT(TO_STR(v) == "3 1 5 4 2");
        ASSERT(TO_REPR(v) == "vector[3, 1, 5, 4, 2]");
    }

    {
        ASSERT(TO_STR(make_tuple()) == "");
        ASSERT(TO_REPR(make_tuple()) == "()");
    }

    {
        auto t = make_tuple(1, "foo", make_pair(3,4));
        ASSERT(TO_STR(t) == "1 foo 3 4");
        ASSERT(TO_REPR(t) == "(1,foo,(3,4))");
    }
}

signed main() {
    test_bit();

    test_sqrt();
    test_log2();
    test_log10();
    test_pow2();
    test_align();

    test_max_min_clamp();

    test_fst_snd();

    test_digit_conv();
    test_lower_conv();
    test_upper_conv();

    test_fmt();

    EXIT();
}
