// prefix_function {{{

template<typename RandomIt>
vector<i64> prefix_function(RandomIt first, RandomIt last) {
    i64 n = last - first;
    vector<i64> pi(n, 0);

    FOR(i, 1, n) {
        i64 j = pi[i-1];
        while(j > 0 && first[i] != first[j])
            j = pi[j-1];
        if(first[i] == first[j])
            ++j;
        pi[i] = j;
    }

    return pi;
}

// }}}
