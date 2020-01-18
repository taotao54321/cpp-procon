// z_function {{{

template<typename RandomIt>
vector<i64> z_function(RandomIt first, RandomIt last) {
    i64 n = last - first;
    vector<i64> z(n, 0);

    i64 l = 0;
    i64 r = 0;
    FOR(i, 1, n) {
        if(i < r)
            z[i] = min(r-i, z[i-l]);

        while(i+z[i] < n && first[i+z[i]] == first[z[i]])
            ++z[i];

        if(chmax(r, i+z[i]))
            l = i;
    }

    z[0] = n;

    return z;
}

// }}}
