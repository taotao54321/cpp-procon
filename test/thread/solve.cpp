#include "procon.hpp"
#include "dynamic_library.hpp"
#include "thread.hpp"

void solve() {
    i64 N = RD();
    i64 K = RD();
    auto A = RD_VEC(N);

    auto f = FIXMEMO<100001>([&A](auto&& self, i64 n) -> bool {
        for(i64 a : A) {
            if(n >= a && !self(n-a))
                return true;
        }
        return false;
    });

    bool ans = f(K);

    PRINTLN(ans ? "First" : "Second");
}

signed main() {
    //auto thre = make_thread(solve, 32*1024*1024);
    auto thre = make_thread([]() { solve(); }, 32*1024*1024);
    thre.join();

    EXIT();
}
