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

// }}}
