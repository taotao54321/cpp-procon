// algorithm {{{

// nPr
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2639.pdf
template<typename BidiIt>
bool next_partial_permutation(BidiIt first, BidiIt middle, BidiIt last) {
    reverse(middle, last);
    return next_permutation(first, last);
}

template<typename BidiIt>
bool prev_partial_permutation(BidiIt first, BidiIt middle, BidiIt last) {
    bool res = prev_permutation(first, last);
    reverse(middle, last);
    return res;
}

// nCr
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2639.pdf
template<typename BidiIt>
bool next_combination_impl(BidiIt first1, BidiIt last1, BidiIt first2, BidiIt last2) {
    if(first1 == last1 || first2 == last2) return false;

    BidiIt m1 = last1;
    BidiIt m2 = last2; --m2;

    while(--m1 != first1 && !(*m1 < *m2));

    bool res = m1 == first1 && !(*first1 < *m2);

    if(!res) {
        while(first2 != m2 && !(*m1 < *first2))
            ++first2;
        first1 = m1;
        iter_swap(first1 ,first2);
        ++first1;
        ++first2;
    }

    if(first1 != last1 && first2 != last2) {
        m1 = last1;
        m2 = first2;
        while(m1 != first1 && m2 != last2) {
            --m1;
            iter_swap(m1 ,m2);
            ++m2;
        }

        reverse(first1, m1);
        reverse(first1, last1);

        reverse(m2, last2);
        reverse(first2, last2);
    }

    return !res;
}

template<typename BidiIt>
bool next_combination(BidiIt first, BidiIt middle, BidiIt last) {
    return next_combination_impl(first, middle, middle, last);
}

template<typename BidiIt>
bool prev_combination(BidiIt first, BidiIt middle, BidiIt last) {
    return next_combination_impl(middle, last, first, middle);
}

template<typename InputIt>
auto nth_value(InputIt first, InputIt last, i64 n) {
    using T = typename iterator_traits<InputIt>::value_type;
    vector<T> v(first, last);
    nth_element(begin(v), begin(v)+n, end(v));
    return v[n];
}

template<typename ForwardIt>
void rotate_left(ForwardIt first, ForwardIt last, i64 n) {
    rotate(first, first+n, last);
}

template<typename ForwardIt>
void rotate_right(ForwardIt first, ForwardIt last, i64 n) {
    auto rfirst = make_reverse_iterator(last);
    auto rlast  = make_reverse_iterator(first);
    rotate(rfirst, rfirst+n, rlast);
}

// [first,last) を隣接2項間で pred が成り立つグループに分ける
// デフォルトでは同じ値のグループに分ける
// 返り値はイテレータ対のリスト
template<typename ForwardIt, typename BinaryPred=equal_to<>>
vector<pair<ForwardIt,ForwardIt>> group_by(ForwardIt first, ForwardIt last, BinaryPred pred={}) {
    vector<pair<ForwardIt,ForwardIt>> res;

    for(auto it = first; it != last; ) {
        auto it2 = it;
        for(;;) {
            auto nex = next(it2);
            if(nex == last) break;
            if(!pred(*it2, *nex)) break;
            it2 = nex;
        }
        it2 = next(it2);

        res.emplace_back(it, it2);
        it = it2;
    }

    return res;
}

// 集合 [first,last) を n 個繰り返したものの直積についてイテレート
// f は bool f(const vector<T>& v)
// f が true を返した時点でイテレーション終了
// 返り値は f が true を返していれば true, さもなくば false
template<typename ForwardIt, typename F>
bool cartesian_product_repeat(ForwardIt first, ForwardIt last, i64 n, F f) {
    using T = typename iterator_traits<ForwardIt>::value_type;

    auto rec = FIX([first,last,n,f](auto&& self, vector<T>& v) -> bool {
        if(SIZE(v) == n)
            return f(const_cast<const vector<T>&>(v));

        for(auto it = first; it != last; ++it) {
            v.emplace_back(*it);
            if(self(v)) return true;
            v.pop_back();
        }
        return false;
    });

    vector<T> v;
    return rec(v);
}

// }}}
