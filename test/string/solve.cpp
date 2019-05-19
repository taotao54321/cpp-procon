#include "procon.hpp"
#include "string.hpp"

void test_is() {
    assert(str_is_digit(CHARS_DIGIT));
    assert(str_is_lower(CHARS_LOWER));
    assert(str_is_upper(CHARS_UPPER));
    assert(str_is_alpha(CHARS_ALPHA));
    assert(str_is_alnum(CHARS_ALNUM));
    assert(str_is_xdigit(CHARS_XDIGIT));

    assert(!str_is_digit("abc"));
    assert(!str_is_lower("123"));
    assert(!str_is_lower("ABC"));
    assert(!str_is_upper("123"));
    assert(!str_is_upper("abc"));
    assert(!str_is_alpha("123"));
    assert(!str_is_alnum("_"));
    assert(!str_is_xdigit("xyz"));
}

void test_to() {
    string s("123aBc_DeF");
    assert(str_to_lower(s) == "123abc_def");
    assert(str_to_upper(s) == "123ABC_DEF");
}

signed main() {
    test_is();
    test_to();

    EXIT();
}
