// cheat {{{

[[noreturn]] void PROCON_MLE(size_t size=1U<<31) {
    static constexpr size_t PAGE_SIZE = 4096;
    volatile char* buf = new char[size];
    for(size_t i = 0; i < size; i += PAGE_SIZE)
        buf[i] = static_cast<char>(i);
    EXIT();
}

[[noreturn]] void PROCON_OLE() {
    static constexpr char BUF[8192] {};
    for(;;)
        cout.write(BUF, SIZE(BUF));
}

[[noreturn]] void PROCON_RE() {
    abort();
}

[[noreturn]] void PROCON_TLE() {
    this_thread::sleep_for(chrono::hours(10000));
    EXIT();
}

[[noreturn]] void PROCON_WA() {
    static constexpr char BUF[256] {
        '\xd1', '\x14', '\xe3', '\xee', '\x3c', '\x37', '\x82', '\x11',
        '\x3f', '\xa7', '\x2a', '\x89', '\xbb', '\x62', '\xad', '\xfc',
        '\xcd', '\x79', '\xfe', '\x0e', '\x0f', '\xe9', '\xdc', '\x23',
        '\x8e', '\x96', '\x7a', '\x5a', '\xfa', '\x56', '\xeb', '\xb9',
        '\xf4', '\xb1', '\x88', '\xe8', '\x05', '\x68', '\x13', '\xd8',
        '\x77', '\x31', '\xc4', '\x64', '\xcc', '\x85', '\x92', '\x22',
        '\xa2', '\xbe', '\x54', '\xfd', '\x3d', '\xce', '\x9a', '\xe2',
        '\x36', '\x47', '\xa9', '\x9d', '\x24', '\x58', '\x2f', '\x1c',
        '\x4f', '\x7b', '\x99', '\xf6', '\x76', '\x70', '\x93', '\x4d',
        '\x6b', '\xc5', '\xc2', '\x4c', '\xd3', '\x86', '\x8d', '\x0d',
        '\x5d', '\x20', '\x3b', '\x4e', '\x8f', '\xa0', '\x98', '\x57',
        '\x9b', '\x6d', '\xb0', '\x12', '\xcf', '\x69', '\x66', '\x27',
        '\x4a', '\x53', '\x60', '\x67', '\x78', '\x87', '\x59', '\xa1',
        '\x43', '\x1b', '\xb5', '\xd4', '\x72', '\x97', '\x34', '\x30',
        '\x06', '\xe0', '\x95', '\x02', '\xbd', '\xd6', '\xf5', '\xc8',
        '\x91', '\x10', '\x90', '\x63', '\x5e', '\x5f', '\xfb', '\xff',
        '\x94', '\x2e', '\xc7', '\xb6', '\xae', '\x50', '\xaa', '\x44',
        '\x0b', '\x6f', '\xc9', '\x83', '\x32', '\x81', '\xb4', '\x2b',
        '\xc6', '\x7c', '\x0a', '\x42', '\x28', '\xb3', '\x48', '\x35',
        '\xea', '\xf3', '\x04', '\x01', '\xf8', '\x08', '\x4b', '\xe5',
        '\xed', '\x49', '\x9f', '\xba', '\x26', '\x29', '\x71', '\xa6',
        '\x09', '\x9c', '\xbc', '\x38', '\xe7', '\x07', '\x8b', '\x1f',
        '\x75', '\xec', '\x1d', '\x1a', '\x7e', '\xa8', '\x8c', '\xd7',
        '\xdb', '\x2d', '\xef', '\x9e', '\xf0', '\xdf', '\x40', '\xb7',
        '\x21', '\x5b', '\xd5', '\x15', '\x45', '\x19', '\x03', '\x7d',
        '\x1e', '\x5c', '\xc3', '\xd9', '\x52', '\xca', '\xda', '\xac',
        '\x80', '\xf2', '\xc0', '\xa4', '\x6a', '\x18', '\x65', '\xb8',
        '\x55', '\x61', '\xab', '\xe6', '\xcb', '\x84', '\xd2', '\xe4',
        '\xbf', '\xdd', '\xb2', '\xe1', '\x16', '\xf9', '\xa3', '\x74',
        '\x0c', '\xde', '\xa5', '\x3a', '\xaf', '\xc1', '\xf1', '\x8a',
        '\x73', '\x51', '\xf7', '\x46', '\x41', '\x25', '\x7f', '\x17',
        '\x00', '\x39', '\x2c', '\xd0', '\x6c', '\x3e', '\x6e', '\x33',
    };
    cout.write(BUF, SIZE(BUF));
    EXIT();
}

// }}}
