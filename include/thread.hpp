// thread (dynamic_library が必要) {{{

template<typename F>
class Thread {
public:
    explicit Thread(F f, std::size_t stacksize) : f_(f) {
        const auto& lib = lib_pthread;
        pthread_attr_t attr;
        call(lib.pthread_attr_init, &attr);
        call(lib.pthread_attr_setstacksize, &attr, stacksize);
        call(lib.pthread_create, &id_, &attr, run, &f_);
        call(lib.pthread_attr_destroy, &attr);
    }

    Thread(const Thread&)            = delete;
    Thread& operator=(const Thread&) = delete;

    // TODO: ムーブ元を無効にすべき
    Thread(Thread&& other) noexcept : f_(other.f_), id_(other.id_) {}
    Thread& operator=(Thread&& other) noexcept {
        if(this == &other) return *this;
        f_  = other.f_;
        id_ = other.id_;
        return *this;
    }

    void join() {
        const auto& lib = lib_pthread;
        call(lib.pthread_join, id_, nullptr);
    }

private:
    template<typename Func, typename... Args>
    void call(Func func, Args... args) {
        int st = func(args...);
        assert(st == 0);
    }

    static void* run(void* p) {
        F* f = static_cast<F*>(p);
        (*f)();
        return nullptr;
    }

    F f_;
    pthread_t id_;
};

template<typename F>
Thread<F> make_thread(F f, std::size_t stacksize) {
    return Thread<F>(f, stacksize);
}

// }}}
