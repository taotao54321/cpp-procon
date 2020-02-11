// sparse_table {{{

template<class T, class Op>
struct SparseTable {
    template<class ForwardIt>
    SparseTable(Op&& op, ForwardIt first, ForwardIt last) : op_(forward<Op>(op)) {
        Int n = distance(first, last);
        Int m = log2_floor(n);
        table_.reserve(m+1);
        table_.emplace_back(vector<T>(first,last));

        FOR(i, 1, m+1) {
            Int len = n - (1LL<<i) + 1;
            vector<T> row(len);
            REP(j, len) {
                row[j] = op_(table_[i-1][j], table_[i-1][j+(1LL<<(i-1))]);
            }
            table_.emplace_back(move(row));
        }
    }

    T query(Int l, Int r) {
        ASSERT_LOCAL(l < r);
        Int i = log2_floor(r-l);
        return op_(table_[i][l], table_[i][r-(1LL<<i)]);
    }

private:
    Op op_;
    vector<vector<T>> table_;
};

template<class T, class Op, class ForwardIt>
auto sparse_table_range(Op&& op, ForwardIt first, ForwardIt last) {
    return SparseTable<T,Op>(forward<Op>(op), first, last);
}

// }}}
