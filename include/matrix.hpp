// matrix {{{

template<class T>
class Matrix {
private:
    vector<vector<T>> mat_;

public:
    static Matrix zeros(Int n) {
        return Matrix(n,n);
    }

    static Matrix eye(Int n) {
        Matrix res(n,n);
        REP(i, n) {
            res.at(i,i) = T(1);
        }
        return res;
    }

    Matrix(Int nr, Int nc) : mat_(nr,vector<T>(nc,T(0))) {}

    Int nrow() const { return SIZE(mat_);    }
    Int ncol() const { return SIZE(mat_[0]); }

    T&       at(Int r, Int c)       { return mat_[r][c]; }
    const T& at(Int r, Int c) const { return mat_[r][c]; }

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
    Matrix pow(Int e) const {
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
        Int nr = lhs.nrow();
        Int nc = rhs.ncol();
        Int m  = lhs.ncol();
        Matrix res(nr,nc);
        REP(r, nr) REP(c, nc) {
            REP(i, m) {
                res.at(r,c) += lhs.at(r,i) * rhs.at(i,c);
            }
        }
        return res;
    }
    friend vector<T> operator*(const Matrix& lhs, const vector<T>& rhs) {
        Int nr = lhs.nrow();
        Int m  = lhs.ncol();
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
    Int nr = lhs.nrow();
    Int nc = rhs.ncol();
    Int m  = lhs.ncol();
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
    Int nr = lhs.nrow();
    Int m  = lhs.ncol();
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
