// {{{ container

template<typename K, typename V, typename Comp, typename KK>
bool map_contains(const map<K,V,Comp>& m, const KK& k) {
    return m.find(k) != end(m);
}

template<typename K, typename V, typename Hash, typename Eq, typename KK>
bool map_contains(const unordered_map<K,V,Hash,Eq>& m, const KK& k) {
    return m.find(k) != end(m);
}

// }}}
