// cum2 {{{

template<class Abel, class Op, class Inv>
struct Cum2 {
    Op op_;
    Inv inv_;
    Abel unity_;

    vector<vector<Abel>> v_;
    bool built_{false};

    Cum2(Op&& op, Inv&& inv, const Abel& unity, i64 h, i64 w) :
        op_(forward<Op>(op)), inv_(forward<Inv>(inv)), unity_(unity),
        v_(h+1,vector<Abel>(w+1,unity_))
    {}

    i64 h() const { return SIZE(v_)-1; }
    i64 w() const { return SIZE(v_[0])-1; }

    const Abel& at(i64 y, i64 x) const {
#ifdef PROCON_LOCAL
        ASSERT(!built_);
#endif
        return v_[y+1][x+1];
    }

    Abel& at(i64 y, i64 x) {
#ifdef PROCON_LOCAL
        ASSERT(!built_);
#endif
        return v_[y+1][x+1];
    }

    void build() {
#ifdef PROCON_LOCAL
        ASSERT(!built_);
#endif
        FOR(y, 1, h()+1) {
            partial_sum(begin(v_[y])+1, end(v_[y]), begin(v_[y])+1, op_);
            FOR(x, 1, w()+1) {
                v_[y][x] = op_(v_[y-1][x], v_[y][x]);
            }
        }
        built_ = true;
    }

    Abel query(i64 y1, i64 x1, i64 y2, i64 x2) const {
#ifdef PROCON_LOCAL
        ASSERT(built_);
        ASSERT(y1 <= y2 && x1 <= x2);
#endif
        Abel res = v_[y2][x2];
        res = op_(res, inv_(v_[y1][x2]));
        res = op_(res, inv_(v_[y2][x1]));
        res = op_(res, v_[y1][x1]);
        return res;
    }
};

template<class Abel, class Op, class Inv>
auto cum2_make(Op&& op, Inv&& inv, const Abel& unity, i64 h, i64 w) {
    return Cum2<Abel,Op,Inv>(forward<Op>(op), forward<Inv>(inv), unity, h, w);
}

template<class T>
auto cum2_default(i64 h, i64 w) {
    return cum2_make<T>(plus<>{}, negate<>{}, T{}, h, w);
}

// }}}
