// fenwick {{{

template<typename T>
struct Fenwick {
    vector<T> v_;

    explicit Fenwick(i64 n) : v_(n+1, T(0)) {}

    void add(i64 i, T x) {
        for(++i; i < SIZE(v_); i += i&(-i)) {
            v_[i] += x;
        }
    }

    T query(i64 i, i64 n) const {
        if(i == 0) return query0(i+n);
        return query0(i+n) - query0(i);
    }

private:
    // [0,n) の和
    T query0(i64 n) const {
        T res(0);
        for(i64 i = n; i > 0; i -= i&(-i)) {
            res += v_[i];
        }
        return res;
    }
};

template<typename T>
struct Formatter<Fenwick<T>> {
    static ostream& write_str(ostream& out, const Fenwick<T>& fenwick) {
        return WRITE_RANGE_STR(out, begin(fenwick.v_), end(fenwick.v_));
    }
    // TODO: 桁数が多くなると崩れる
    static ostream& write_repr(ostream& out, const Fenwick<T>& fenwick) {
        i64 n = SIZE(fenwick.v_) - 1;

        out << "Fenwick {\n";
        for(i64 i = pow2_floor(n); i > 0; i >>= 1) {
            string space((1LL<<(log2_floor(i)+1))-1, ' ');
            for(i64 j = i; j <= n; j += (i<<1)) {
                WRITE_REPR(out, fenwick.v_[j]);
                out << space;
            }
            out << "\n";
        }
        out << "}";
        return out;
    }
};

// }}}
