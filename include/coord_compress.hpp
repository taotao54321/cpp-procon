// coord_compress {{{

// xs は破壊される
template<typename Comp>
void coord_compress(vector<i64>& xs, map<i64,i64,Comp>& m) {
    ALL(sort, xs);
    UNIQ(xs);
    REP(i, SIZE(xs)) {
        m.emplace(xs[i], i);
    }
}

// xs は破壊される
template<typename Hash, typename Eq>
void coord_compress(vector<i64>& xs, unordered_map<i64,i64,Hash,Eq>& m) {
    ALL(sort, xs);
    UNIQ(xs);
    REP(i, SIZE(xs)) {
        m.emplace(xs[i], i);
    }
}

// }}}
