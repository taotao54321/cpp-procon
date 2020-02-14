// lis_dp {{{

// longest increasing subsequence のDP配列を返す
// decreasing にしたければ comp=greater<>{} とする
// 戻り値 dp[i]: 位置 i を末尾とする部分列の最大長
template<class RandomIt, class Comp=less<>>
auto lis_dp(RandomIt first, RandomIt last, Comp comp={}) {
    Int n = last - first;

    vector<Int> is(n);
    ALL(iota, is, 0);
    ALL(sort, is, [first,comp](Int il, Int ir) {
        if(comp(first[il], first[ir])) return true;
        if(comp(first[ir], first[il])) return false;
        return il < ir;
    });

    vector<Int> fenwick(n+1, 0);
    vector<Int> dp(n);
    for(Int i : is) {
        Int x = 0;
        for(Int j = i; j >= 1; j -= j&(-j))
            chmax(x, fenwick[j]);
        ++x;
        dp[i] = x;
        for(Int j = i+1; j < n+1; j += j&(-j))
            chmax(fenwick[j], x);
    }

    return dp;
}

// longest STRICTLY increasing subsequence のDP配列を返す
// decreasing にしたければ comp=greater<>{} とする
// 戻り値 dp[i]: 位置 i を末尾とする部分列の最大長
template<class RandomIt, class Comp=less<>>
auto lis_strict_dp(RandomIt first, RandomIt last, Comp comp={}) {
    Int n = last - first;

    vector<Int> is(n);
    ALL(iota, is, 0);
    ALL(sort, is, [first,comp](Int il, Int ir) {
        if(comp(first[il], first[ir])) return true;
        if(comp(first[ir], first[il])) return false;
        return ir < il;
    });

    vector<Int> fenwick(n+1, 0);
    vector<Int> dp(n);
    for(Int i : is) {
        Int x = 0;
        for(Int j = i; j >= 1; j -= j&(-j))
            chmax(x, fenwick[j]);
        ++x;
        dp[i] = x;
        for(Int j = i+1; j < n+1; j += j&(-j))
            chmax(fenwick[j], x);
    }

    return dp;
}

// }}}
