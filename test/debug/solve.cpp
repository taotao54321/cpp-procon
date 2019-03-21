#include "procon.hpp"
#include "debug.hpp"

void test_container() {
    {
        deque<i64> deq { 2, 4, 1, 5, 3 };
        assert(TO_STR(deq) == "deque[2, 4, 1, 5, 3]");
    }
}

signed main() {
    test_container();

    return 0;
}
