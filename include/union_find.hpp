struct UnionFind {
    vector<i64> ps_;  // 親ノード。ただし根の場合 -(集合の要素数)

    explicit UnionFind(i64 n) : ps_(n,-1) {}

    i64 root(i64 x) {
        i64 p = ps_[x];
        if(p < 0) return x;
        return ps_[x] = root(p);
    }

    void unite(i64 x, i64 y) {
        i64 rx = root(x);
        i64 ry = root(y);
        if(rx == ry) return;

        // 要素数が大きい方を根とする
        i64 kx = -ps_[rx];
        i64 ky = -ps_[ry];
        if(kx < ky) swap(rx, ry);
        ps_[rx] = -(kx + ky);
        ps_[ry] = rx;
    }
};
