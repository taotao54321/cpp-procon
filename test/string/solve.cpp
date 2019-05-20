#include "procon.hpp"
#include "string.hpp"

void test_is() {
    ASSERT(str_is_digit(CHARS_DIGIT));
    ASSERT(str_is_lower(CHARS_LOWER));
    ASSERT(str_is_upper(CHARS_UPPER));
    ASSERT(str_is_alpha(CHARS_ALPHA));
    ASSERT(str_is_alnum(CHARS_ALNUM));
    ASSERT(str_is_xdigit(CHARS_XDIGIT));

    ASSERT(!str_is_digit("abc"));
    ASSERT(!str_is_lower("123"));
    ASSERT(!str_is_lower("ABC"));
    ASSERT(!str_is_upper("123"));
    ASSERT(!str_is_upper("abc"));
    ASSERT(!str_is_alpha("123"));
    ASSERT(!str_is_alnum("_"));
    ASSERT(!str_is_xdigit("xyz"));
}

void test_to() {
    string s("123aBc_DeF");
    ASSERT(str_to_lower(s) == "123abc_def");
    ASSERT(str_to_upper(s) == "123ABC_DEF");
}

signed main() {
    test_is();
    test_to();

    EXIT();
}
