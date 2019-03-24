// matrix {{{

template<typename T>
class Matrix {
private:
    vector<vector<T>> mat_;

public:
    static Matrix zeros(i64 n) {
        return Matrix(n,n);
    }

    static Matrix eye(i64 n) {
        Matrix res(n,n);
        REP(i, n) {
            res.at(i,i) = T(1);
        }
        return res;
    }

    Matrix(i64 nr, i64 nc) : mat_(nr,vector<T>(nc,T(0))) {}

    i64 nrow() const { return SIZE(mat_);    }
    i64 ncol() const { return SIZE(mat_[0]); }

    T&       at(i64 r, i64 c)       { return mat_[r][c]; }
    const T& at(i64 r, i64 c) const { return mat_[r][c]; }

    Matrix operator-() const {
        REP(r, nrow()) REP(c, ncol()) {
            at(r,c) = -at(r,c);
        }
    }
    Matrix& operator+=(const Matrix& rhs) {
        REP(r, nrow()) REP(c, ncol()) {
            at(r,c) += rhs.at(r,c);
        }
        return *this;
    }
    Matrix& operator-=(const Matrix& rhs) {
        REP(r, nrow()) REP(c, ncol()) {
            at(r,c) -= rhs.at(r,c);
        }
        return *this;
    }
    Matrix& operator*=(T x) {
        REP(r, nrow()) REP(c, ncol()) {
            at(r,c) *= x;
        }
    }
    Matrix& operator/=(T x) {
        REP(r, nrow()) REP(c, ncol()) {
            at(r,c) /= x;
        }
    }
    Matrix& operator*=(const Matrix& rhs) {
        return *this = *this * rhs;
    }

    // 正方行列であること
    Matrix pow(i64 e) const {
        assert(e >= 0);

        Matrix res = eye(nrow());
        Matrix cur = *this;
        while(e > 0) {
            if(e & 1)
                res *= cur;
            cur *= cur;
            e >>= 1;
        }
        return res;
    }
};

template<typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return Matrix<T>(lhs) += rhs;
}

template<typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return Matrix<T>(lhs) -= rhs;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs, T rhs) {
    return Matrix<T>(lhs) *= rhs;
}

template<typename T>
Matrix<T> operator*(T lhs, const Matrix<T>& rhs) {
    return Matrix<T>(rhs) *= lhs;
}

template<typename T>
Matrix<T> operator/(const Matrix<T>& lhs, T rhs) {
    return Matrix<T>(lhs) /= rhs;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    i64 nr = lhs.nrow();
    i64 nc = rhs.ncol();
    i64 m  = lhs.ncol();
    Matrix<T> res(nr,nc);
    REP(r, nr) REP(c, nc) {
        REP(i, m) {
            res.at(r,c) += lhs.at(r,i) * rhs.at(i,c);
        }
    }
    return res;
}

template<typename T>
vector<T> operator*(const Matrix<T>& lhs, const vector<T>& rhs) {
    i64 nr = lhs.nrow();
    i64 m  = lhs.ncol();
    vector<T> res(m, T(0));
    REP(r, nr) {
        REP(i, m) {
            res[r] += lhs.at(r,i) * rhs[i];
        }
    }
    return res;
}

template<typename T>
struct Formatter<Matrix<T>> {
    static ostream& write_str(ostream& out, const Matrix<T>& m) {
        return write_repr(out, m);
    }
    static ostream& write_repr(ostream& out, const Matrix<T>& m) {
        out << "Matrix[";
        REP(r, m.nrow()) {
            if(r != 0) out << ",";
            out << "[";
            REP(c, m.ncol()) {
                if(c != 0) out << ",";
                WRITE_REPR(out, m.at(r,c));
            }
            out << "]";
        }
        out << "]";
        return out;
    }
};

// }}}
