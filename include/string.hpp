// string {{{
// ASCII を仮定

const string CHARS_DIGIT("0123456789");
const string CHARS_LOWER("abcdefghijklmnopqrstuvwxyz");
const string CHARS_UPPER("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const string CHARS_ALPHA("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
const string CHARS_ALNUM("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
const string CHARS_XDIGIT("0123456789abcdefABCDEF");

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

bool is_lower(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_upper(char c) {
    return 'A' <= c && c <= 'Z';
}

bool is_alpha(char c) {
    return is_lower(c) || is_upper(c);
}

bool is_alnum(char c) {
    return is_alpha(c) || is_digit(c);
}

bool is_xdigit(char c) {
    return is_digit(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F');
}

bool str_is_digit(const string& s) {
    return ALL(all_of, s, is_digit);
}

bool str_is_lower(const string& s) {
    return ALL(all_of, s, is_lower);
}

bool str_is_upper(const string& s) {
    return ALL(all_of, s, is_upper);
}

bool str_is_alpha(const string& s) {
    return ALL(all_of, s, is_alpha);
}

bool str_is_alnum(const string& s) {
    return ALL(all_of, s, is_alnum);
}

bool str_is_xdigit(const string& s) {
    return ALL(all_of, s, is_xdigit);
}

char to_lower(char c) {
    return is_upper(c) ? static_cast<char>(c+0x20) : c;
}

char to_upper(char c) {
    return is_lower(c) ? static_cast<char>(c-0x20) : c;
}

string str_to_lower(const string& s) {
    string res;
    res.reserve(SIZE(s));
    ALL(transform, s, back_inserter(res), to_lower);
    return res;
}

string str_to_upper(const string& s) {
    string res;
    res.reserve(SIZE(s));
    ALL(transform, s, back_inserter(res), to_upper);
    return res;
}

// }}}
