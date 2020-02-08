// bench {{{

Int get_ticks_ms() {
    static const auto START = chrono::high_resolution_clock::now();
    auto now = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now-START).count();
}

template<typename F>
Int bench(F&& f) {
    Int start = get_ticks_ms();
    f();
    Int end = get_ticks_ms();
    return end - start;
}

// }}}
