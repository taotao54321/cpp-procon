// container {{{

// hash {{{
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
auto set_search_lt(set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    auto it = s.lower_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_lt(const set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    auto it = s.lower_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_le(set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    auto it = s.upper_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_le(const set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    auto it = s.upper_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_gt(set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    return s.upper_bound(x);
}

template<typename T, typename Comp>
auto set_search_gt(const set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    return s.upper_bound(x);
}

template<typename T, typename Comp>
auto set_search_ge(set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    return s.lower_bound(x);
}

template<typename T, typename Comp>
auto set_search_ge(const set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    return s.lower_bound(x);
}
// }}}
// map {{{
template<typename K, typename V, typename Comp>
auto map_search_lt(map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& x) {
    auto it = m.lower_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_lt(const map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& x) {
    auto it = m.lower_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_le(map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& x) {
    auto it = m.upper_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_le(const map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& x) {
    auto it = m.upper_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_gt(map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& x) {
    return m.upper_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_gt(const map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& x) {
    return m.upper_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_ge(map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& x) {
    return m.lower_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_ge(const map<K,V,Comp>& m, const typename map<K,V,Comp>::key_type& x) {
    return m.lower_bound(x);
}
// }}}
// multiset {{{
// 等価な値が複数ある場合、lt/le は先頭を、gt/ge は末尾を指す
template<typename T, typename Comp>
auto set_search_lt(multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    auto it = s.lower_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_lt(const multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    auto it = s.lower_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_le(multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    auto it = s.upper_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_le(const multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    auto it = s.upper_bound(x);
    if(it == begin(s)) return end(s);
    return prev(it);
}

template<typename T, typename Comp>
auto set_search_gt(multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    return s.upper_bound(x);
}

template<typename T, typename Comp>
auto set_search_gt(const multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    return s.upper_bound(x);
}

template<typename T, typename Comp>
auto set_search_ge(multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    return s.lower_bound(x);
}

template<typename T, typename Comp>
auto set_search_ge(const multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    return s.lower_bound(x);
}
// }}}
// multimap {{{
// 等価な値が複数ある場合、lt/le は先頭を、gt/ge は末尾を指す
template<typename K, typename V, typename Comp>
auto map_search_lt(multimap<K,V,Comp>& m, const typename multimap<K,V,Comp>::key_type& x) {
    auto it = m.lower_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_lt(const multimap<K,V,Comp>& m, const typename multimap<K,V,Comp>::key_type& x) {
    auto it = m.lower_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_le(multimap<K,V,Comp>& m, const typename multimap<K,V,Comp>::key_type& x) {
    auto it = m.upper_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_le(const multimap<K,V,Comp>& m, const typename multimap<K,V,Comp>::key_type& x) {
    auto it = m.upper_bound(x);
    if(it == begin(m)) return end(m);
    return prev(it);
}

template<typename K, typename V, typename Comp>
auto map_search_gt(multimap<K,V,Comp>& m, const typename multimap<K,V,Comp>::key_type& x) {
    return m.upper_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_gt(const multimap<K,V,Comp>& m, const typename multimap<K,V,Comp>::key_type& x) {
    return m.upper_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_ge(multimap<K,V,Comp>& m, const typename multimap<K,V,Comp>::key_type& x) {
    return m.lower_bound(x);
}

template<typename K, typename V, typename Comp>
auto map_search_ge(const multimap<K,V,Comp>& m, const typename multimap<K,V,Comp>::key_type& x) {
    return m.lower_bound(x);
}
// }}}
// }}}

template<typename T, typename Comp>
bool set_contains(const set<T,Comp>& s, const typename set<T,Comp>::key_type& x) {
    return s.find(x) != end(s);
}

template<typename T, typename Hash, typename Eq>
bool set_contains(const unordered_set<T,Hash,Eq>& s, const typename unordered_set<T,Hash,Eq>::key_type& x) {
    return s.find(x) != end(s);
}

template<typename T, typename Comp>
bool set_contains(const multiset<T,Comp>& s, const typename multiset<T,Comp>::key_type& x) {
    return s.find(x) != end(s);
}

template<typename T, typename Hash, typename Eq>
bool set_contains(const unordered_multiset<T,Hash,Eq>& s, const typename unordered_multiset<T,Hash,Eq>::key_type& x) {
    return s.find(x) != end(s);
}

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

template<typename K, typename V, typename Comp>
V map_get(const map<K,V,Comp>& m,
          const typename map<K,V,Comp>::key_type& k,
          const typename map<K,V,Comp>::mapped_type& def)
{
    auto it = m.find(k);
    return it == end(m) ? def : it->second;
}

template<typename K, typename V, typename Hash, typename Eq>
V map_get(const unordered_map<K,V,Hash,Eq>& m,
          const typename unordered_map<K,V,Hash,Eq>::key_type& k,
          const typename unordered_map<K,V,Hash,Eq>::mapped_type& def)
{
    auto it = m.find(k);
    return it == end(m) ? def : it->second;
}

template<typename K, typename V, typename Comp>
V& map_setdefault(map<K,V,Comp>& m,
                  const typename map<K,V,Comp>::key_type& k,
                  const typename map<K,V,Comp>::mapped_type& def)
{
    auto it = m.find(k);
    if(it == end(m))
        it = m.emplace_hint(it, k, def);
    return it->second;
}

template<typename K, typename V, typename Hash, typename Eq>
V& map_setdefault(unordered_map<K,V,Hash,Eq>& m,
                  const typename unordered_map<K,V,Hash,Eq>::key_type& k,
                  const typename unordered_map<K,V,Hash,Eq>::mapped_type& def)
{
    auto it = m.find(k);
    if(it == end(m))
        it = m.emplace_hint(it, k, def);
    return it->second;
}

template<typename K, typename V, typename Comp, typename F>
V& map_setdefault_with(map<K,V,Comp>& m,
                       const typename map<K,V,Comp>::key_type& k,
                       F&& f)
{
    auto it = m.find(k);
    if(it == end(m))
        it = m.emplace_hint(it, k, f());
    return it->second;
}

template<typename K, typename V, typename Hash, typename Eq, typename F>
V& map_setdefault_with(unordered_map<K,V,Hash,Eq>& m,
                       const typename unordered_map<K,V,Hash,Eq>::key_type& k,
                       F&& f)
{
    auto it = m.find(k);
    if(it == end(m))
        it = m.emplace_hint(it, k, f());
    return it->second;
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

// bimap {{{
template<typename T1, typename T2>
struct BiHashMap {
    HashMap<T1,T2> fwd_;
    HashMap<T2,T1> rev_;

    void insert(const T1& x, const T2& y) {
        auto it_fwd = fwd_.find(x);
        if(it_fwd == end(fwd_)) {
            fwd_.insert(it_fwd, make_pair(x,y));
            rev_.insert(end(rev_), make_pair(y,x));
        }
        else {
            ASSERT(y == it_fwd->second);
        }
    }

    bool contains_fwd(const T1& x) const {
        return map_contains(fwd_, x);
    }

    bool contains_rev(const T2& y) const {
        return map_contains(rev_, y);
    }

    const T2& at_fwd(const T1& x) const {
        auto it = fwd_.find(x);
        ASSERT(it != end(fwd_));
        return it->second;
    }

    const T1& at_rev(const T2& y) const {
        auto it = rev_.find(y);
        ASSERT(it != end(rev_));
        return it->second;
    }

    size_t size() const { return fwd_.size(); }
};
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
