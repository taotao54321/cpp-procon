// coord_compress {{{

struct CoordCompress {
    vector<i64> xs_;
    unordered_map<i64,i64> comp_;
    bool built_{false};

    CoordCompress() = default;

    explicit CoordCompress(i64 cap) {
        xs_.reserve(cap);
    }

    template<class InputIt>
    CoordCompress(InputIt first, InputIt last) : xs_(first,last) {}

    i64 size() const { return SIZE(xs_); }

    void insert(i64 x) {
        ASSERT_LOCAL(!built_);
        xs_.emplace_back(x);
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last) {
        ASSERT_LOCAL(!built_);
        xs_.insert(end(xs_), first, last);
    }

    void insert(initializer_list<i64> ilist) {
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

    i64 comp(i64 x) const {
        ASSERT_LOCAL(built_);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnull-dereference"
        return comp_.find(x)->second;
#pragma GCC diagnostic pop
    }

    i64 uncomp(i64 i) const {
        ASSERT_LOCAL(built_);
        return xs_[i];
    }

    i64 lower_bound(i64 x) const {
        ASSERT_LOCAL(built_);
        return distance(begin(xs_), ALL(std::lower_bound, xs_, x));
    }

    i64 upper_bound(i64 x) const {
        ASSERT_LOCAL(built_);
        return distance(begin(xs_), ALL(std::upper_bound, xs_, x));
    }
};

// }}}
