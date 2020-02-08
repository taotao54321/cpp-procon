// coord_compress {{{

struct CoordCompress {
    vector<Int> xs_;
    unordered_map<Int,Int> comp_;
    bool built_{false};

    CoordCompress() = default;

    explicit CoordCompress(Int cap) {
        xs_.reserve(cap);
    }

    template<class InputIt>
    CoordCompress(InputIt first, InputIt last) : xs_(first,last) {}

    Int size() const { return SIZE(xs_); }

    void insert(Int x) {
        ASSERT_LOCAL(!built_);
        xs_.emplace_back(x);
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last) {
        ASSERT_LOCAL(!built_);
        xs_.insert(end(xs_), first, last);
    }

    void insert(initializer_list<Int> ilist) {
        insert(begin(ilist), end(ilist));
    }

    void build() {
        ASSERT_LOCAL(!built_);

        ALL(sort, xs_);
        xs_.erase(ALL(unique,xs_), end(xs_));

        REP(i, SIZE(xs_)) {
            comp_.emplace(xs_[i], i);
        }

        built_ = true;
    }

    Int comp(Int x) const {
        ASSERT_LOCAL(built_);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnull-dereference"
        return comp_.find(x)->second;
#pragma GCC diagnostic pop
    }

    Int uncomp(Int i) const {
        ASSERT_LOCAL(built_);
        return xs_[i];
    }

    Int lower_bound(Int x) const {
        ASSERT_LOCAL(built_);
        return distance(begin(xs_), ALL(std::lower_bound, xs_, x));
    }

    Int upper_bound(Int x) const {
        ASSERT_LOCAL(built_);
        return distance(begin(xs_), ALL(std::upper_bound, xs_, x));
    }
};

// }}}
