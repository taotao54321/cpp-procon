// z_function {{{

template<class RandomIt>
vector<Int> z_function(RandomIt first, RandomIt last) {
    Int n = last - first;
    vector<Int> z(n, 0);

    Int l = 0;
    Int r = 0;
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
