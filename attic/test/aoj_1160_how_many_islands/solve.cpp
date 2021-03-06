#include "procon.hpp"
#include "grid.hpp"

void solve(i64 H, i64 W) {
    auto grid = RD_GRID2<i64>(H,W);

    auto dfs = FIX([&grid](auto&& self, const Index2& idx) -> void {
        grid[idx] = 0;
        for(const auto& to : grid.neighbor8(idx)) {
            if(grid[to] == 0) continue;
            self(to);
        }
    });

    i64 ans = 0;
    REP(y, H) REP(x, W) {
        if(grid.at(y,x) == 1) {
            ++ans;
            dfs(Index2(y,x));
        }
    }

    PRINTLN(ans);
}

signed main() {
    for(;;) {
        i64 W = RD();
        i64 H = RD();
        if(H == 0 && W == 0) break;
        solve(H, W);
    }

    EXIT();
}
