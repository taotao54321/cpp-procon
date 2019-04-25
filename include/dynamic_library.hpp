// dynamic_library {{{

extern "C" {
    void* __libc_dlclose(void*);
    void* __libc_dlopen_mode(const char*, int);
    void* __libc_dlsym(void*, const char*);
}

class DynamicLibrary {
private:
    static constexpr int OPEN_MODE = 2;  // RTLD_NOW
    void* handle_;

public:
    explicit DynamicLibrary(const char* path) : handle_(__libc_dlopen_mode(path,OPEN_MODE)) {
        assert(handle_);
    }
    ~DynamicLibrary() {
        if(handle_)
            __libc_dlclose(handle_);
    }

    void* sym(const char* name) {
        void* res = __libc_dlsym(handle_, name);
        assert(res);
        return res;
    }
};

#include <pthread.h>

class DynamicLibrary_pthread {
private:
    DynamicLibrary handle_;

public:
#define DEF_FUNC(name) decltype(::name)* const name
    DEF_FUNC(pthread_attr_destroy);
    DEF_FUNC(pthread_attr_init);
    DEF_FUNC(pthread_attr_setstacksize);
    DEF_FUNC(pthread_create);
    DEF_FUNC(pthread_join);
#undef DEF_FUNC

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconditionally-supported"
#define SYM_GET(name) name(reinterpret_cast<decltype(::name)*>(handle_.sym(CPP_STR(name))))
    explicit DynamicLibrary_pthread(const char* path) : handle_(path),
        SYM_GET(pthread_attr_destroy),
        SYM_GET(pthread_attr_init),
        SYM_GET(pthread_attr_setstacksize),
        SYM_GET(pthread_create),
        SYM_GET(pthread_join)
    {}
#undef SYM_GET
#pragma GCC diagnostic pop
};

DynamicLibrary_pthread lib_pthread("/lib/x86_64-linux-gnu/libpthread.so.0");  // atcoder

// }}}
