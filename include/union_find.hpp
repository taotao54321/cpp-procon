// union_find {{{

struct UnionFind {
    vector<i64> ps_;  // 親ノード。ただし根の場合 -(集合の要素数)
    i64 size_;

    explicit UnionFind(i64 n) : ps_(n,-1), size_(n) {}

    i64 size() const { return size_; }

    i64 root(i64 x) {
        i64 p = ps_[x];
        if(p < 0) return x;
        return ps_[x] = root(p);
    }

    bool is_same(i64 x, i64 y) {
        return root(x) == root(y);
    }

    i64 group_size(i64 x) {
        return -ps_[root(x)];
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

        --size_;
    }
};

struct WeightedUnionFind {
    vector<i64> ps_;  // 親ノード。ただし根の場合 -(集合の要素数)
    vector<i64> ws_;  // 親ノードに対する重み(負もOK)。根の場合0
    i64 size_;

    explicit WeightedUnionFind(i64 n) : ps_(n,-1), ws_(n,0), size_(n) {}

    i64 size() const { return size_; }

    i64 root(i64 x) {
        return get<0>(compress(x));
    }

    bool is_same(i64 x, i64 y) {
        return root(x) == root(y);
    }

    i64 group_size(i64 x) {
        return -ps_[root(x)];
    }

    // 根に対する重み
    i64 weight(i64 x) {
        return get<1>(compress(x));
    }

    // x, y を併合する
    // x に対する y の重みを d とする
    // 併合できたかどうかを返す
    // x, y が元々同一集合に属する場合、d の値によっては矛盾が生じて併合不能
    /*[[nodiscard]]*/ bool unite(i64 x, i64 y, i64 d) {
        i64 rx, ry, wx, wy;
        tie(rx,wx) = compress(x);
        tie(ry,wy) = compress(y);
        if(rx == ry) return wx + d == wy;

        // 要素数が大きい方を根とする
        i64 kx = -ps_[rx];
        i64 ky = -ps_[ry];
        if(kx < ky) {
            swap(rx, ry);
            swap(wx, wy);
            d *= -1;
        }
        ps_[rx] = -(kx + ky);
        ps_[ry] = rx;
        ws_[ry] = wx - wy + d;

        --size_;

        return true;
    }

private:
    // 経路圧縮
    // (xの根、根に対するxの重み) を返す
    tuple<i64,i64> compress(i64 x) {
        i64 p = ps_[x];
        if(p < 0) return make_tuple(x, 0);

        i64 r,d; tie(r,d) = compress(p);
        ps_[x]  = r;
        ws_[x] += d;
        return make_tuple(r, ws_[x]);
    }
};

// }}}
