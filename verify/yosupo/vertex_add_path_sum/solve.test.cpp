#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
//#define ERROR "1e-6"

#define ASSERT_LV 2
// header {{{
#include "../../../include/stdc++.hpp"
using namespace std;

#include "../../../include/types.hpp"
// }}}

using Int  = i64;
using Real = f80;

constexpr Int MOD = 1'000'000'007;
//constexpr Int MOD = 998'244'353;

constexpr Real EPS = Real(1e-10L);

constexpr int  COUT_PREC      = 15;
constexpr bool COUT_AUTOFLUSH = false;

#include "../../../include/procon.hpp"
#include "../../../include/euler_tour.hpp"
#include "../../../include/lca.hpp"
#include "../../../include/fenwick.hpp"

//--------------------------------------------------------------------

void solve() {
    Int N = RD();
    Int Q = RD();
    auto A = RD_VEC(N);

    // 頂点vの値を「頂点vへ降りてくる辺の重み」に変換する
    // そのために新たな根を設ける
    ++N;
    Int root = N-1;
    // 木を構築。とりあえず重みは0としておく
    vector<vector<pair<Int,Int>>> G(N);
    G[root].emplace_back(0, 0);
    G[0].emplace_back(root, 0);
    LOOP(N-2) {
        Int a = RD();
        Int b = RD();
        G[a].emplace_back(b, 0);
        G[b].emplace_back(a, 0);
    }
    // DFSで適切に重みを設定
    auto dfs = FIX([&](auto&& self, Int v, Int p) -> void {
        for(auto& e : G[v]) {
            Int to = e.first;
            if(to == p) continue;
            e.second = A[to];
            self(to, v);
        }
    });
    dfs(root, -1);

    vector<Int> ds,us,ws; tie(ds,us,ws) = euler_tour_edge(G, root);

    Fenwick<Int> fen(2*N);
    REP(i, 2*N) {
        fen.add(i, ws[i]);
    }

    Lca lca(G, root);

    LOOP(Q) {
        Int cmd = RD();
        if(cmd == 0) {
            Int v = RD();
            Int x = RD();

            fen.add(ds[v],  x);
            fen.add(us[v], -x);
        }
        else if(cmd == 1) {
            Int v = RD();
            Int w = RD();

            Int z = lca.query(v, w);
            Int ans = fen.query0(ds[v]+1) + fen.query0(ds[w]+1) - 2*fen.query0(ds[z]+1) + fen.query(ds[z],ds[z]+1);
            PRINTLN(ans);
        }
        else { ASSERT(false); }
    }
}

signed main() {
    solve();

    EXIT();
}
