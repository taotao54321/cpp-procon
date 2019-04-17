// suffix_array {{{

template<typename ForwardIt>
struct SuffixArray {
    using value_type      = i64;
    using const_reference = const value_type&;
    using const_iterator  = typename vector<value_type>::const_iterator;
    using difference_type = typename vector<value_type>::difference_type;
    using size_type       = typename vector<value_type>::size_type;

    ForwardIt first_;
    ForwardIt last_;
    vector<value_type> sa_;

    SuffixArray(ForwardIt first, ForwardIt last) 
        : first_(first), last_(last), sa_(distance(first,last)+1)
    {
        i64 n = distance(first_,last_);
        vector<i64> rnk(n+1);

        ALL(iota, sa_, 0);
        copy(first_, last_, std::begin(rnk));
        rnk[n] = -1;

        vector<i64> rnk_nex(n+1);
        for(i64 k = 1; k <= n; k *= 2) {  // TODO: 条件部の等号いらない気がするんだが…
            auto comp = LT_ON([n,&rnk,k](i64 i) {
                i64 snd = i+k <= n ? rnk[i+k] : -1;
                return make_pair(rnk[i], snd);
            });

            ALL(sort, sa_, comp);

            rnk_nex[sa_[0]] = 0;
            FOR(i, 1, n+1) {
                rnk_nex[sa_[i]] = rnk_nex[sa_[i-1]] + (comp(sa_[i-1],sa_[i]) ? 1 : 0);
            }
            swap(rnk, rnk_nex);
        }
    }

    const_iterator begin() const { return std::begin(sa_); }
    const_iterator end()   const { return std::end(sa_); }

    const_iterator cbegin() const { return std::cbegin(sa_); }
    const_iterator cend()   const { return std::cend(sa_); }

    template<typename ForwardIt2>
    const_iterator find(ForwardIt2 first2, ForwardIt2 last2) const {
        auto x = make_pair(first2,last2);
        auto comp = Compare<ForwardIt2>(first_, last_);
        auto it = ALL(std::lower_bound, sa_, x, comp);
        if(it == end() || comp(x,*it)) return end();
        return it;
    }

    template<typename ForwardIt2>
    pair<const_iterator,const_iterator> equal_range(ForwardIt2 first2, ForwardIt2 last2) const {
        auto comp = Compare<ForwardIt2>(first_, last_);
        return ALL(std::equal_range, sa_, make_pair(first2,last2), comp);
    }

    template<typename ForwardIt2>
    struct Compare {
        ForwardIt first_;
        ForwardIt last_;

        Compare(ForwardIt first, ForwardIt last) : first_(first), last_(last) {}

        bool operator()(i64 i, const pair<ForwardIt2,ForwardIt2>& p) const {
            auto q = get_range(i, distance(FST(p),SND(p)));
            return lexicographical_compare(FST(q), SND(q), FST(p), SND(p));
        }
        bool operator()(const pair<ForwardIt2,ForwardIt2>& p, i64 i) const {
            auto q = get_range(i, distance(FST(p),SND(p)));
            return lexicographical_compare(FST(p), SND(p), FST(q), SND(q));
        }

        pair<ForwardIt,ForwardIt> get_range(i64 i, i64 n) const {
            auto first1 = first_ + i;
            auto last1  = first_ + i;
            advance_bounded(first_, last_, last1, n);
            return make_pair(first1, last1);
        }
    };
};

template<typename ForwardIt>
SuffixArray<ForwardIt> make_suffix_array(ForwardIt first, ForwardIt last) {
    return SuffixArray<ForwardIt>(first, last);
}

// }}}
