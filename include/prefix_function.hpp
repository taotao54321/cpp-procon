// prefix_function {{{

template<class RandomIt>
vector<Int> prefix_function(RandomIt first, RandomIt last) {
    Int n = last - first;
    vector<Int> pi(n, 0);

    FOR(i, 1, n) {
        Int j = pi[i-1];
        while(j > 0 && first[i] != first[j])
            j = pi[j-1];
        if(first[i] == first[j])
            ++j;
        pi[i] = j;
    }

    return pi;
}

// }}}
