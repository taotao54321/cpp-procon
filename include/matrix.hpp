// matrix {{{

template<class T>
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
        Matrix res(*this);
        REP(r, nrow()) REP(c, ncol()) {
            res.at(r,c) = -at(r,c);
        }
        return res;
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
        return fastpow(*this, e, eye(nrow()));
    }

    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
        return Matrix(lhs) += rhs;
    }
    friend Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
        return Matrix(lhs) -= rhs;
    }
    friend Matrix operator*(const Matrix& lhs, T rhs) {
        return Matrix(lhs) *= rhs;
    }
    friend Matrix operator*(T lhs, const Matrix& rhs) {
        return Matrix(rhs) *= lhs;
    }
    friend Matrix operator/(const Matrix& lhs, T rhs) {
        return Matrix(lhs) /= rhs;
    }
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        i64 nr = lhs.nrow();
        i64 nc = rhs.ncol();
        i64 m  = lhs.ncol();
        Matrix res(nr,nc);
        REP(r, nr) REP(c, nc) {
            REP(i, m) {
                res.at(r,c) += lhs.at(r,i) * rhs.at(i,c);
            }
        }
        return res;
    }
    friend vector<T> operator*(const Matrix& lhs, const vector<T>& rhs) {
        i64 nr = lhs.nrow();
        i64 m  = lhs.ncol();
        vector<T> res(m, T{});
        REP(r, nr) {
            REP(i, m) {
                res[r] += lhs.at(r,i) * rhs[i];
            }
        }
        return res;
    }
};
#if 0
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
#endif
// }}}
