// two_pointer {{{

// しゃくとり法
// 各 l に対し条件 f(l,r) が真になる最大の r を求める
// f(空区間) は常に真とする
class TwoPointer {
private:
    Int n_;
    Int l_, r_;

    virtual void init() {}

    // 0 <= l < r <= n が保証される
    virtual void forward_l(Int /*l*/, Int /*r*/) {}

    // [l,r+1) が条件を満たさないなら false を返す(この場合 r は変化しない)
    // 0 <= l <= r < n が保証される
    virtual bool forward_r(Int /*l*/, Int /*r*/) = 0;

    // 各 l についてちょうど 1 回だけ呼ばれる
    // false を返すことで処理を中断できる
    // 0 <= l <= r <= n が保証される
    virtual bool on_found(Int l, Int r) = 0;

protected:
    explicit TwoPointer(Int n) : n_(n) {}

public:
    void run() {
        init();

        for(l_=0, r_=0; l_ < n_; ++l_) {
            for(;;) {
                if(r_ == n_) break;
                if(!forward_r(l_, r_)) break;
                ++r_;
            }

            bool cont = on_found(l_, r_);
            if(!cont) break;

            if(l_ == r_)
                ++r_;
            else
                forward_l(l_, r_);
        }
    }

    Int size() const { return n_; }
};

// 継承用テンプレ(差分計算なし)
#if 0
struct TP : TwoPointer {
    const vector<Int>& A_;
    Int ans_;

    TP(const vector<Int>& A) : TwoPointer(SIZE(A)), A_(A) {}

    void init() override {
        
    }

    bool forward_r(Int l, Int r) override {
        
    }

    bool on_found(Int l, Int r) override {
        
        return true;
    }
};
#endif

// 継承用テンプレ(差分計算あり)
#if 0
struct TP : TwoPointer {
    const vector<Int>& A_;
    Int ans_;

    TP(const vector<Int>& A) : TwoPointer(SIZE(A)), A_(A) {}

    void init() override {
        
    }

    void forward_l(Int l, Int) override {
        
    }

    bool forward_r(Int, Int r) override {
        
    }

    bool on_found(Int l, Int r) override {
        
        return true;
    }
};
#endif

// }}}
