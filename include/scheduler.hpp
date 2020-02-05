// scheduler {{{

class ProconTimer {
private:
    using Clock = chrono::steady_clock;
    chrono::time_point<Clock> start_;

public:
    ProconTimer() : start_(Clock::now()) {}

    Real get_ms() const {
        auto now = Clock::now();
        chrono::duration<Real,std::milli> dur = now - start_;
        return dur.count();
    }
} TIMER;

// Scheduler sched(1980.0);  // 起動からの経過時間
// do {
//     // ある程度の回数ループ
// } while(sched.next_ok());
class Scheduler {
public:
    Scheduler(Real deadline) : deadline_(deadline), start_(TIMER.get_ms()), prev_(start_) {
        ASSERT(start_ < deadline_);
    }

    bool next_ok() {
        Real now = TIMER.get_ms();
        Real dt  = now - prev_;
        ++iter_cnt_;
        sum_sq_ += dt*dt;

        Real mean     = (now-start_) / iter_cnt_;
        Real variance = sum_sq_/iter_cnt_ - mean*mean;
        Real stddev   = sqrt(variance);
        prev_ = now;

        return now+mean+2*stddev < deadline_;
    }

    Real elapsed_ratio() const {
        return (prev_-start_) / (deadline_-start_);
    }

private:
    Real deadline_;
    Real start_;
    Real prev_;
    int  iter_cnt_{};
    Real sum_sq_{};
};

// }}}
