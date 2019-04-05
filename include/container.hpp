// container {{{

// hash {{{
template<typename T>
struct procon_hash {
    size_t operator()(const T& x) const {
        return hash<T>()(x);
    }
};

template<typename T>
size_t procon_hash_value(const T& x) {
    return procon_hash<T>()(x);
}

template<typename T>
void procon_hash_combine(size_t& seed, const T& x) {
    seed ^= procon_hash_value(x) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template<typename InputIt>
void procon_hash_range(size_t& seed, InputIt first, InputIt last) {
    for(; first != last; ++first)
        procon_hash_combine(seed, *first);
}

template<typename InputIt>
size_t procon_hash_range(InputIt first, InputIt last) {
    size_t seed = 0;
    procon_hash_range(seed, first, last);
    return seed;
}

template<typename T1, typename T2>
struct procon_hash<pair<T1,T2>> {
    size_t operator()(const pair<T1,T2>& p) const {
        size_t seed = 0;
        procon_hash_combine(seed, p.first);
        procon_hash_combine(seed, p.second);
        return seed;
    }
};

template<typename T, typename Eq=equal_to<T>>
using HashSet = unordered_set<T,procon_hash<T>,Eq>;

template<typename K, typename V, typename Eq=equal_to<K>>
using HashMap = unordered_map<K,V,procon_hash<K>,Eq>;

template<typename T, typename Eq=equal_to<T>>
using HashMultiset = unordered_multiset<T,procon_hash<T>,Eq>;

template<typename K, typename V, typename Eq=equal_to<K>>
using HashMultimap = unordered_multimap<K,V,procon_hash<K>,Eq>;
// }}}

template<typename T>
using MaxHeap = priority_queue<T, vector<T>, less<T>>;
template<typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

// set/map/multiset/multimap search {{{
// set {{{
template<typename T, typename Comp>
auto set_search_lt(set<T,Comp>& s, const T& x) {
    auto it = s.lower_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_lt(const set<T,Comp>& s, const T& x) {
    auto it = s.lower_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_le(set<T,Comp>& s, const T& x) {
    auto it = s.upper_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_le(const set<T,Comp>& s, const T& x) {
    auto it = s.upper_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_gt(set<T,Comp>& s, const T& x) {
    return s.upper_bound(x);
}

template<typename T, typename Comp>
auto set_search_gt(const set<T,Comp>& s, const T& x) {
    return s.upper_bound(x);
}

template<typename T, typename Comp>
auto set_search_ge(set<T,Comp>& s, const T& x) {
    return s.lower_bound(x);
}

template<typename T, typename Comp>
auto set_search_ge(const set<T,Comp>& s, const T& x) {
    return s.lower_bound(x);
}
// }}}
// map {{{
template<typename K, typename V, typename Comp>
auto map_search_lt(map<K,V,Comp>& m, const K& x) {
    auto it = m.lower_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_lt(const map<K,V,Comp>& m, const K& x) {
    auto it = m.lower_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_le(map<K,V,Comp>& m, const K& x) {
    auto it = m.upper_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_le(const map<K,V,Comp>& m, const K& x) {
    auto it = m.upper_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_gt(map<K,V,Comp>& m, const K& x) {
    return m.upper_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_gt(const map<K,V,Comp>& m, const K& x) {
    return m.upper_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_ge(map<K,V,Comp>& m, const K& x) {
    return m.lower_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_ge(const map<K,V,Comp>& m, const K& x) {
    return m.lower_bound(x);
}
// }}}
// multiset {{{
template<typename T, typename Comp>
auto set_search_lt(multiset<T,Comp>& s, const T& x) {
    auto it = s.lower_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_lt(const multiset<T,Comp>& s, const T& x) {
    auto it = s.lower_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_le(multiset<T,Comp>& s, const T& x) {
    auto it = s.upper_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_le(const multiset<T,Comp>& s, const T& x) {
    auto it = s.upper_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_gt(multiset<T,Comp>& s, const T& x) {
    return s.upper_bound(x);
}

template<typename T, typename Comp>
auto set_search_gt(const multiset<T,Comp>& s, const T& x) {
    return s.upper_bound(x);
}

template<typename T, typename Comp>
auto set_search_ge(multiset<T,Comp>& s, const T& x) {
    return s.lower_bound(x);
}

template<typename T, typename Comp>
auto set_search_ge(const multiset<T,Comp>& s, const T& x) {
    return s.lower_bound(x);
}
// }}}
// multimap {{{
template<typename K, typename V, typename Comp>
auto map_search_lt(multimap<K,V,Comp>& m, const K& x) {
    auto it = m.lower_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_lt(const multimap<K,V,Comp>& m, const K& x) {
    auto it = m.lower_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_le(multimap<K,V,Comp>& m, const K& x) {
    auto it = m.upper_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_le(const multimap<K,V,Comp>& m, const K& x) {
    auto it = m.upper_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_gt(multimap<K,V,Comp>& m, const K& x) {
    return m.upper_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_gt(const multimap<K,V,Comp>& m, const K& x) {
    return m.upper_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_ge(multimap<K,V,Comp>& m, const K& x) {
    return m.lower_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_ge(const multimap<K,V,Comp>& m, const K& x) {
    return m.lower_bound(x);
}
// }}}
// }}}

template<typename K, typename V, typename Comp>
bool map_contains(const map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& k) {
    return m.find(k) != end(m);
}

template<typename K, typename V, typename Hash, typename Eq>
bool map_contains(const unordered_map<K,V,Hash,Eq>& m, const typename unordered_map<K,V,Hash,Eq>::key_type& k) {
    return m.find(k) != end(m);
}

template<typename K, typename V, typename Comp>
bool map_contains(const multimap<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& k) {
    return m.find(k) != end(m);
}

template<typename K, typename V, typename Hash, typename Eq>
bool map_contains(const unordered_multimap<K,V,Hash,Eq>& m, const typename unordered_map<K,V,Hash,Eq>::key_type& k) {
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

// POP() 系 {{{
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
// }}}

// Formatter {{{
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
// }}}

// }}}
