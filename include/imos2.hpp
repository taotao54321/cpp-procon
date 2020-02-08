// imos2 {{{

template<class Abel, class Op, class Inv>
struct Imos2 {
    Op op_;
    Inv inv_;
    Abel unity_;

    vector<vector<Abel>> v_;
    bool built_{false};

    Imos2(Op&& op, Inv&& inv, const Abel& unity, Int h, Int w) :
        op_(forward<Op>(op)), inv_(forward<Inv>(inv)), unity_(unity),
        v_(h+1,vector<Abel>(w+1,unity_))
    {}

    Int h() const { return SIZE(v_)-1; }
    Int w() const { return SIZE(v_[0])-1; }

    // [(y1,x1),(y2,x2))
    void add(Int y1, Int x1, Int y2, Int x2, const Abel& val) {
        ASSERT_LOCAL(!built_);

        v_[y1][x1] = op_(v_[y1][x1], val);
        v_[y2][x1] = op_(v_[y2][x1], inv_(val));
        v_[y1][x2] = op_(v_[y1][x2], inv_(val));
        v_[y2][x2] = op_(v_[y2][x2], val);
    }

    void build() {
        ASSERT_LOCAL(!built_);

        REP(y, h()) {
            REP(x, w()-1) {
                v_[y][x+1] = op_(v_[y][x+1], v_[y][x]);
            }
            if(y == 0) continue;
            REP(x, w()) {
                v_[y][x] = op_(v_[y][x], v_[y-1][x]);
            }
        }

        built_ = true;
    }

    const Abel& at(Int y, Int x) const {
        ASSERT_LOCAL(built_);
        return v_[y][x];
    }
};

template<class Abel, class Op, class Inv>
auto imos2_make(Op&& op, Inv&& inv, const Abel& unity, Int h, Int w) {
    return Imos2<Abel,Op,Inv>(forward<Op>(op), forward<Inv>(inv), unity, h, w);
}

template<class T>
auto imos2_default(Int h, Int w) {
    return imos2_make<T>(plus<>{}, negate<>{}, T{}, h, w);
}

// }}}
