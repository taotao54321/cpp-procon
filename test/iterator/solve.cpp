#include "procon.hpp"
#include "iterator.hpp"

signed main() {
    {
        static_assert( IS_INPUT_ITERATOR<istream_iterator<int>>::value, "");
        static_assert(!IS_FORWARD_ITERATOR<istream_iterator<int>>::value, "");
        static_assert(!IS_BIDIRECTIONAL_ITERATOR<istream_iterator<int>>::value, "");
        static_assert(!IS_RANDOM_ACCESS_ITERATOR<istream_iterator<int>>::value, "");
    }
    {
        i64 cont[10];
        static_assert( IS_INPUT_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_FORWARD_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_BIDIRECTIONAL_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_RANDOM_ACCESS_ITERATOR<decltype(begin(cont))>::value, "");
    }
    {
        vector<i64> cont;
        static_assert( IS_INPUT_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_FORWARD_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_BIDIRECTIONAL_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_RANDOM_ACCESS_ITERATOR<decltype(begin(cont))>::value, "");
    }
    {
        forward_list<i64> cont;
        static_assert( IS_INPUT_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_FORWARD_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert(!IS_BIDIRECTIONAL_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert(!IS_RANDOM_ACCESS_ITERATOR<decltype(begin(cont))>::value, "");
    }
    {
        list<i64> cont;
        static_assert( IS_INPUT_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_FORWARD_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert( IS_BIDIRECTIONAL_ITERATOR<decltype(begin(cont))>::value, "");
        static_assert(!IS_RANDOM_ACCESS_ITERATOR<decltype(begin(cont))>::value, "");
    }

    EXIT();
}
