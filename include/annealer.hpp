// annealer {{{

template<class TempF, class ProbF>
class Annealer {
public:
    Annealer(TempF&& ft, ProbF&& fp, Real temp_start, Real temp_end) :
        ft_(forward<TempF>(ft)), fp_(forward<ProbF>(fp)),
        temp_start_(temp_start), temp_end_(temp_end), temp_(temp_start_)
    {}

    Real temp() const { return temp_; }

    Real prob(Real dscore) const {
        return dscore > 0 ? 1.0 : fp_(temp_,dscore);
    }

    void update(Real r) {
        temp_ = ft_(temp_start_, temp_end_, r);
#ifdef PROCON_LOCAL
        ++n_update_;
#endif
    }

    bool accepts(Real dscore) {
        if(dscore > 0) return true;
        Real p = fp_(temp_, dscore);
        bool ok = dist_(PROCON_URBG()) < p;
#ifdef PROCON_LOCAL
        if(ok) ++n_accept_;
#endif
        return ok;
    }

#ifdef PROCON_LOCAL
    Int update_count() const { return n_update_; }
    Int accept_count() const { return n_accept_; }
#endif

private:
    TempF ft_;
    ProbF fp_;
    Real temp_start_;
    Real temp_end_;
    Real temp_;
    uniform_real_distribution<Real> dist_{};
#ifdef PROCON_LOCAL
    Int n_update_{};
    Int n_accept_{};
#endif
};

template<class TempF, class ProbF>
auto annealer_make(TempF&& ft, ProbF&& fp, Real temp_start, Real temp_end) {
    return Annealer<TempF,ProbF>(forward<TempF>(ft), forward<ProbF>(fp), temp_start, temp_end);
}

auto annealer_default(Real temp_start, Real temp_end) {
    return annealer_make(
        [](Real ts, Real te, Real r) { return ts + r*(te-ts); },
        [](Real temp, Real dscore) { return exp(dscore/temp); },
        temp_start, temp_end
    );
}

// }}}
