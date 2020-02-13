// lca {{{

struct Lca {
    Lca(const vector<vector<Int>>& g, Int root) :
        n_(SIZE(g)), m_(log2_floor(n_)), depths_(n_),
        pss_(m_+1,vector<Int>(n_,-1))
    {
        init_dfs(g, root, -1, 0);

        FOR(i, 1, m_+1) {
            REP(v, n_) {
                Int p = pss_[i-1][v];
                if(p == -1) continue;
                pss_[i][v] = pss_[i-1][p];
            }
        }
    }

    template<class T>
    Lca(const vector<vector<pair<Int,T>>>& g, Int root) :
        n_(SIZE(g)), m_(log2_floor(n_)), depths_(n_),
        pss_(m_+1,vector<Int>(n_,-1))
    {
        init_dfs_w(g, root, -1, 0);

        FOR(i, 1, m_+1) {
            REP(v, n_) {
                Int p = pss_[i-1][v];
                if(p == -1) continue;
                pss_[i][v] = pss_[i-1][p];
            }
        }
    }

    Int query(Int v, Int w) const {
        if(depths_[v] > depths_[w]) swap(v, w);

        for(Int i = m_; i >= 0; --i) {
            Int dd = depths_[w] - depths_[v];
            if(dd == 0) break;
            if(BIT_TEST(dd,i))
                w = pss_[i][w];
        }
        if(v == w) return v;

        for(Int i = m_; i >= 0; --i) {
            Int pv = pss_[i][v];
            Int pw = pss_[i][w];
            if(pv != pw) {
                v = pv;
                w = pw;
            }
        }
        return pss_[0][v];
    }

    Int depth(Int v) const { return depths_[v]; }

private:
    void init_dfs(const vector<vector<Int>>& g, Int v, Int p, Int d) {
        depths_[v] = d;
        pss_[0][v] = p;
        for(Int to : g[v]) {
            if(to == p) continue;
            init_dfs(g, to, v, d+1);
        }
    }

    template<class T>
    void init_dfs_w(const vector<vector<pair<Int,T>>>& g, Int v, Int p, Int d) {
        depths_[v] = d;
        pss_[0][v] = p;
        for(const auto& e : g[v]) {
            Int to = e.first;
            if(to == p) continue;
            init_dfs_w(g, to, v, d+1);
        }
    }

    Int n_;
    Int m_;
    vector<Int> depths_;
    vector<vector<Int>> pss_;
};

// }}}
