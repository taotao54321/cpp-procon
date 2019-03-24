// {{{ cum (build() 忘れに注意)

// 1次元累積和
template<typename T>
struct Cum1 {
    vector<T> v_;

    explicit Cum1(i64 n) : v_(n+1, T(0)) {}

    void add(i64 i, T val) {
        v_[i+1] += val;
    }

    void build() {
        ALL(partial_sum, v_, begin(v_));
    }

    T query(i64 i, i64 n) const {
        return v_[i+n] - v_[i];
    }
};

// 2次元累積和
template<typename T>
struct Cum2 {
    vector<vector<T>> v_;

    Cum2(i64 h, i64 w) : v_(h+1, vector<T>(w+1, T(0))) {}

    void add(i64 y, i64 x, T val) {
        v_[y+1][x+1] += val;
    }

    void build() {
        i64 h = SIZE(v_) - 1;
        FOR(y, 1, h+1) {
            ALL(partial_sum, v_[y], begin(v_[y]));
            ALL(transform, v_[y-1], begin(v_[y]), begin(v_[y]), plus<>());
        }
    }

    T query(i64 y, i64 x, i64 h, i64 w) const {
        return v_[y+h][x+w] - v_[y+h][x] - v_[y][x+w] + v_[y][x];
    }
};

// }}}
