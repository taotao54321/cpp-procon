// union_find {{{

struct UnionFind {
    vector<Int> ps_;  // 親ノード。ただし根の場合 -(集合の要素数)
    Int size_;

    explicit UnionFind(Int n) : ps_(n,-1), size_(n) {}

    Int size() const { return size_; }

    Int root(Int x) {
        Int p = ps_[x];
        if(p < 0) return x;
        return ps_[x] = root(p);
    }

    bool is_same(Int x, Int y) {
        return root(x) == root(y);
    }

    Int group_size(Int x) {
        return -ps_[root(x)];
    }

    void unite(Int x, Int y) {
        Int rx = root(x);
        Int ry = root(y);
        if(rx == ry) return;

        // 要素数が大きい方を根とする
        Int kx = -ps_[rx];
        Int ky = -ps_[ry];
        if(kx < ky) swap(rx, ry);
        ps_[rx] = -(kx + ky);
        ps_[ry] = rx;

        --size_;
    }
};

template<class T>
struct WeightedUnionFind {
    vector<Int> ps_;  // 親ノード。ただし根の場合 -(集合の要素数)
    vector<T>   ws_;  // 親ノードに対する重み(負もOK)。根の場合0
    Int size_;

    explicit WeightedUnionFind(Int n) : ps_(n,-1), ws_(n,T{}), size_(n) {}

    Int size() const { return size_; }

    Int root(Int x) {
        return get<0>(compress(x));
    }

    bool is_same(Int x, Int y) {
        return root(x) == root(y);
    }

    Int group_size(Int x) {
        return -ps_[root(x)];
    }

    // 根に対する重み
    T weight(Int x) {
        return get<1>(compress(x));
    }

    // x, y を併合する
    // x に対する y の重みを d とする
    // 併合できたかどうかを返す
    // x, y が元々同一集合に属する場合、d の値によっては矛盾が生じて併合不能
    /*[[nodiscard]]*/ bool unite(Int x, Int y, T d) {
        Int rx, ry;
        T   wx, wy;
        tie(rx,wx) = compress(x);
        tie(ry,wy) = compress(y);
        if(rx == ry) return wx + d == wy;

        // 要素数が大きい方を根とする
        Int kx = -ps_[rx];
        Int ky = -ps_[ry];
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
    tuple<Int,T> compress(Int x) {
        Int p = ps_[x];
        if(p < 0) return make_tuple(x, T{});

        Int r; T d; tie(r,d) = compress(p);
        ps_[x]  = r;
        ws_[x] += d;
        return make_tuple(r, ws_[x]);
    }
};

// }}}
