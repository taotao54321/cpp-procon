// {{{ container

// {{{ BoolArray
class BoolArray {
public:
    using value_type      = bool;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using iterator        = value_type*;
    using const_iterator  = const value_type*;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;

    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    BoolArray() : BoolArray(0) {}
    explicit BoolArray(size_t n) : BoolArray(n,false) {}
    BoolArray(size_t n, bool value) : size_(n), data_(new bool[n]) {
        ALL(fill, *this, value);
    }

    BoolArray(initializer_list<bool> init) : size_(init.size()), data_(new bool[size_]) {
        ALL(copy, init, begin());
    }

    template<typename InputIt>
    BoolArray(InputIt first, InputIt last) {
        deque<bool> tmp(first, last);
        size_ = tmp.size();
        data_ = new bool[size_];
        ALL(copy, tmp, begin());
    }

    BoolArray(const BoolArray& other) : size_(other.size_), data_(new bool[size_]) {
        ALL(copy, other, begin());
    }

    BoolArray(BoolArray&& other) : size_(other.size_), data_(other.data_) {
        other.data_ = nullptr;
    }

    BoolArray& operator=(const BoolArray& other) {
        if(this == &other) return *this;
        if(!data_ || size_ < other.size_) {
            delete[] data_;
            data_ = new bool[other.size_];
        }
        size_ = other.size_;
        ALL(copy, other, begin());
        return *this;
    }

    BoolArray& operator=(BoolArray&& other) {
        if(this == &other) return *this;
        size_ = other.size_;
        data_ = other.data_;
        other.data_ = nullptr;
    }

    BoolArray& operator=(initializer_list<bool> init) {
        if(!data_ || size_ < init.size()) {
            delete[] data_;
            data_ = new bool[init.size()];
        }
        size_ = init.size();
        ALL(copy, init, begin());
        return *this;
    }

    void swap(BoolArray& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    ~BoolArray() {
        delete[] data_;
        data_ = nullptr;
    }

    bool      empty()    const noexcept { return size_ == 0; }
    size_type size()     const noexcept { return size_; }
    size_type max_size() const noexcept { return INF; }

    iterator       begin()        noexcept { return data_; }
    const_iterator begin()  const noexcept { return data_; }
    const_iterator cbegin() const noexcept { return data_; }

    iterator       end()        noexcept { return data_+size_; }
    const_iterator end()  const noexcept { return data_+size_; }
    const_iterator cend() const noexcept { return data_+size_; }

    reverse_iterator       rbegin()        noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    reverse_iterator       rend()        noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend()  const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    reference       operator[](size_type pos)       { return data_[pos]; }
    const_reference operator[](size_type pos) const { return data_[pos]; }

    bool*       data()       noexcept { return data_; }
    const bool* data() const noexcept { return data_; }

private:
    size_t size_;
    bool*  data_;
};

void swap(BoolArray& lhs, BoolArray& rhs) noexcept { lhs.swap(rhs); }

bool operator==(const BoolArray& lhs, const BoolArray& rhs) {
    return equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
}
bool operator!=(const BoolArray& lhs, const BoolArray& rhs) { return !(lhs == rhs); }

bool operator<(const BoolArray& lhs, const BoolArray& rhs) {
    return lexicographical_compare(begin(lhs), end(lhs), begin(rhs), end(rhs));
}
bool operator> (const BoolArray& lhs, const BoolArray& rhs) { return rhs < lhs; }
bool operator<=(const BoolArray& lhs, const BoolArray& rhs) { return !(rhs < lhs); }
bool operator>=(const BoolArray& lhs, const BoolArray& rhs) { return !(lhs < rhs); }
// }}}

template<typename K, typename V, typename Comp>
bool map_contains(const map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& k) {
    return m.find(k) != end(m);
}

template<typename K, typename V, typename Hash, typename Eq>
bool map_contains(const unordered_map<K,V,Hash,Eq>& m, const typename unordered_map<K,V,Hash,Eq>::key_type& k) {
    return m.find(k) != end(m);
}

template<typename K, typename Comp>
bool multiset_erase_one(multiset<K,Comp>& m, const typename multiset<K,Comp>::key_type& k) {
    auto it = m.find(k);
    if(it == end(m)) return false;
    m.erase(it);
    return true;
}

template<typename K, typename Hash, typename Eq>
bool multiset_erase_one(unordered_multiset<K,Hash,Eq>& m, const typename unordered_multiset<K,Hash,Eq>::key_type& k) {
    auto it = m.find(k);
    if(it == end(m)) return false;
    m.erase(it);
    return true;
}

template<typename T>
using MaxHeap = priority_queue<T, vector<T>, less<T>>;
template<typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

// 効率は悪い
template<typename T>
T POP_FRONT(vector<T>& v) {
    T x = v.front(); v.erase(begin(v));
    return x;
}

template<typename T>
T POP_BACK(vector<T>& v) {
    T x = v.back(); v.pop_back();
    return x;
}

template<typename T>
T POP_FRONT(deque<T>& v) {
    T x = v.front(); v.pop_front();
    return x;
}

template<typename T>
T POP_BACK(deque<T>& v) {
    T x = v.back(); v.pop_back();
    return x;
}

template<typename T>
T POP_FRONT(forward_list<T>& ls) {
    T x = ls.front(); ls.pop_front();
    return x;
}

template<typename T>
T POP_FRONT(list<T>& ls) {
    T x = ls.front(); ls.pop_front();
    return x;
}

template<typename T>
T POP_BACK(list<T>& ls) {
    T x = ls.back(); ls.pop_back();
    return x;
}

template<typename T, typename C>
T POP(stack<T,C>& stk) {
    T x = stk.top(); stk.pop();
    return x;
}

template<typename T, typename C>
T POP(queue<T,C>& que) {
    T x = que.front(); que.pop();
    return x;
}

template<typename T, typename C, typename Comp>
T POP(priority_queue<T,C,Comp>& que) {
    T x = que.top(); que.pop();
    return x;
}

template<typename T, size_t N>
struct Formatter<array<T,N>> {
    static ostream& write_str(ostream& out, const array<T,N>& a) {
        return WRITE_RANGE_STR(out, begin(a), end(a));
    }
    static ostream& write_repr(ostream& out, const array<T,N>& a) {
        out << "array";
        return WRITE_RANGE_REPR(out, begin(a), end(a));
    }
};

template<typename T>
struct Formatter<deque<T>> {
    static ostream& write_str(ostream& out, const deque<T>& deq) {
        return WRITE_RANGE_STR(out, begin(deq), end(deq));
    }
    static ostream& write_repr(ostream& out, const deque<T>& deq) {
        out << "deque";
        return WRITE_RANGE_REPR(out, begin(deq), end(deq));
    }
};

template<typename T>
struct Formatter<forward_list<T>> {
    static ostream& write_str(ostream& out, const forward_list<T>& ls) {
        return WRITE_RANGE_STR(out, begin(ls), end(ls));
    }
    static ostream& write_repr(ostream& out, const forward_list<T>& ls) {
        out << "forward_list";
        return WRITE_RANGE_REPR(out, begin(ls), end(ls));
    }
};

template<typename T>
struct Formatter<list<T>> {
    static ostream& write_str(ostream& out, const list<T>& ls) {
        return WRITE_RANGE_STR(out, begin(ls), end(ls));
    }
    static ostream& write_repr(ostream& out, const list<T>& ls) {
        out << "list";
        return WRITE_RANGE_REPR(out, begin(ls), end(ls));
    }
};

template<typename T, typename Comp>
struct Formatter<set<T,Comp>> {
    static ostream& write_str(ostream& out, const set<T,Comp>& s) {
        return WRITE_RANGE_STR(out, begin(s), end(s));
    }
    static ostream& write_repr(ostream& out, const set<T,Comp>& s) {
        out << "set";
        return WRITE_RANGE_REPR(out, begin(s), end(s));
    }
};

template<typename T, typename Comp>
struct Formatter<multiset<T,Comp>> {
    static ostream& write_str(ostream& out, const multiset<T,Comp>& s) {
        return WRITE_RANGE_STR(out, begin(s), end(s));
    }
    static ostream& write_repr(ostream& out, const multiset<T,Comp>& s) {
        out << "multiset";
        return WRITE_RANGE_REPR(out, begin(s), end(s));
    }
};

template<typename T, typename Hash, typename Eq>
struct Formatter<unordered_set<T,Hash,Eq>> {
    static ostream& write_str(ostream& out, const unordered_set<T,Hash,Eq>& s) {
        return WRITE_RANGE_STR(out, begin(s), end(s));
    }
    static ostream& write_repr(ostream& out, const unordered_set<T,Hash,Eq>& s) {
        out << "unordered_set";
        return WRITE_RANGE_REPR(out, begin(s), end(s));
    }
};

template<typename T, typename Hash, typename Eq>
struct Formatter<unordered_multiset<T,Hash,Eq>> {
    static ostream& write_str(ostream& out, const unordered_multiset<T,Hash,Eq>& s) {
        return WRITE_RANGE_STR(out, begin(s), end(s));
    }
    static ostream& write_repr(ostream& out, const unordered_multiset<T,Hash,Eq>& s) {
        out << "unordered_multiset";
        return WRITE_RANGE_REPR(out, begin(s), end(s));
    }
};

template<typename K, typename V, typename Comp>
struct Formatter<map<K,V,Comp>> {
    static ostream& write_str(ostream& out, const map<K,V,Comp>& m) {
        return WRITE_RANGE_STR(out, begin(m), end(m));
    }
    static ostream& write_repr(ostream& out, const map<K,V,Comp>& m) {
        out << "map";
        return WRITE_RANGE_REPR(out, begin(m), end(m));
    }
};

template<typename K, typename V, typename Comp>
struct Formatter<multimap<K,V,Comp>> {
    static ostream& write_str(ostream& out, const multimap<K,V,Comp>& m) {
        return WRITE_RANGE_STR(out, begin(m), end(m));
    }
    static ostream& write_repr(ostream& out, const multimap<K,V,Comp>& m) {
        out << "multimap";
        return WRITE_RANGE_REPR(out, begin(m), end(m));
    }
};

template<typename K, typename V, typename Hash, typename Eq>
struct Formatter<unordered_map<K,V,Hash,Eq>> {
    static ostream& write_str(ostream& out, const unordered_map<K,V,Hash,Eq>& m) {
        return WRITE_RANGE_STR(out, begin(m), end(m));
    }
    static ostream& write_repr(ostream& out, const unordered_map<K,V,Hash,Eq>& m) {
        out << "unordered_map";
        return WRITE_RANGE_REPR(out, begin(m), end(m));
    }
};

template<typename K, typename V, typename Hash, typename Eq>
struct Formatter<unordered_multimap<K,V,Hash,Eq>> {
    static ostream& write_str(ostream& out, const unordered_multimap<K,V,Hash,Eq>& m) {
        return WRITE_RANGE_STR(out, begin(m), end(m));
    }
    static ostream& write_repr(ostream& out, const unordered_multimap<K,V,Hash,Eq>& m) {
        out << "unordered_multimap";
        return WRITE_RANGE_REPR(out, begin(m), end(m));
    }
};

template<typename T, typename C>
struct Formatter<stack<T,C>> {
    static ostream& write_str(ostream& out, const stack<T,C>& orig) {
        stack<T,C> stk(orig);
        while(!stk.empty()) {
            WRITE_STR(out, stk.top()); stk.pop();
            if(!stk.empty()) out << ' ';
        }
        return out;
    }
    static ostream& write_repr(ostream& out, const stack<T,C>& orig) {
        stack<T,C> stk(orig);
        out << "stack[";
        while(!stk.empty()) {
            WRITE_REPR(out, stk.top()); stk.pop();
            if(!stk.empty()) out << ", ";
        }
        out << "]";
        return out;
    }
};

template<typename T, typename C>
struct Formatter<queue<T,C>> {
    static ostream& write_str(ostream& out, const queue<T,C>& orig) {
        queue<T,C> que(orig);
        while(!que.empty()) {
            WRITE_STR(out, que.front()); que.pop();
            if(!que.empty()) out << ' ';
        }
        return out;
    }
    static ostream& write_repr(ostream& out, const queue<T,C>& orig) {
        queue<T,C> que(orig);
        out << "queue[";
        while(!que.empty()) {
            WRITE_REPR(out, que.front()); que.pop();
            if(!que.empty()) out << ", ";
        }
        out << "]";
        return out;
    }
};

template<typename T, typename C, typename Comp>
struct Formatter<priority_queue<T,C,Comp>> {
    static ostream& write_str(ostream& out, const priority_queue<T,C,Comp>& orig) {
        priority_queue<T,C,Comp> que(orig);
        while(!que.empty()) {
            WRITE_STR(out, que.top()); que.pop();
            if(!que.empty()) out << ' ';
        }
        return out;
    }
    static ostream& write_repr(ostream& out, const priority_queue<T,C,Comp>& orig) {
        priority_queue<T,C,Comp> que(orig);
        out << "priority_queue[";
        while(!que.empty()) {
            WRITE_REPR(out, que.top()); que.pop();
            if(!que.empty()) out << ", ";
        }
        out << "]";
        return out;
    }
};

template<>
struct Formatter<BoolArray> {
    static ostream& write_str(ostream& out, const BoolArray& a) {
        return WRITE_RANGE_STR(out, begin(a), end(a));
    }
    static ostream& write_repr(ostream& out, const BoolArray& a) {
        out << "BoolArray";
        return WRITE_RANGE_REPR(out, begin(a), end(a));
    }
};

// }}}
