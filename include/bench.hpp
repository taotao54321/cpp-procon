// bench {{{

i64 get_ticks_ms() {
    static const auto START = chrono::high_resolution_clock::now();
    auto now = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now-START).count();
}

template<typename F>
i64 bench(F&& f) {
    i64 start = get_ticks_ms();
    f();
    i64 end = get_ticks_ms();
    return end - start;
}

// }}}
