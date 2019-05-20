// debug {{{

template<typename T, SFINAE(rank<T>::value == 0)>
ostream& DBG_CARRAYN_HELPER(ostream& out, const T& e) {
    return WRITE_REPR(out, e);
}

template<typename T, SFINAE(rank<T>::value != 0)>
ostream& DBG_CARRAYN_HELPER(ostream& out, const T& e) {
    out << "[";
    for(auto it = begin(e); it != end(e); ++it) {
        if(it != begin(e))
            out << ", ";
        DBG_CARRAYN_HELPER(out, *it);
    }
    out << "]";
    return out;
}

template<typename T>
void DBG_CARRAYN_IMPL(i64 line, const char* expr, const T& ary) {
    cerr << "[L " << line << "]: ";
    cerr << expr << " = ";
    DBG_CARRAYN_HELPER(cerr, ary);
    cerr << "\n";
}

template<typename T, typename... Offs, typename... Sizes,
         SFINAE(rank<T>::value == 0 && sizeof...(Offs) == 0 && sizeof...(Sizes) == 0)>
ostream& DBG_CARRAYN_SLICE_HELPER(ostream& out, const T& e, const tuple<Offs...>&, const tuple<Sizes...>&) {
    return WRITE_REPR(out, e);
}

template<typename T, typename... Offs, typename... Sizes,
         SFINAE(rank<T>::value != 0 && sizeof...(Offs) > 0 && sizeof...(Sizes) > 0)>
ostream& DBG_CARRAYN_SLICE_HELPER(ostream& out, const T& e, const tuple<Offs...>& offs, const tuple<Sizes...>& sizes) {
    static_assert(rank<T>::value == sizeof...(Offs));
    out << "[";
    i64 l = tuple_head(offs);
    i64 r = l + tuple_head(sizes);
    FOR(i, l, r) {
        if(i != l)
            out << ", ";
        DBG_CARRAYN_SLICE_HELPER(out, e[i], tuple_tail(offs), tuple_tail(sizes));
    }
    out << "]";
    return out;
}

template<typename T, typename... Offs, typename... Sizes>
void DBG_CARRAYN_SLICE_IMPL(i64 line, const char* expr, const T& ary, const tuple<Offs...>& offs, const tuple<Sizes...>& sizes) {
    cerr << "[L " << line << "]: ";
    cerr << expr << "(";
    WRITE_REPR(cerr, offs);
    cerr << ",";
    WRITE_REPR(cerr, sizes);
    cerr << ") = ";
    DBG_CARRAYN_SLICE_HELPER(cerr, ary, offs, sizes);
    cerr << "\n";
}

#ifdef PROCON_LOCAL
    #define DBG_CARRAYN(expr) DBG_CARRAYN_IMPL(__LINE__, CPP_STR(expr), (expr))
    #define DBG_CARRAYN_SLICE(expr, offs, sizes) DBG_CARRAYN_SLICE_IMPL(__LINE__, CPP_STR(expr), (expr), (offs), (sizes))
#else
    #define DBG_CARRAYN(expr)
    #define DBG_CARRAYN_SLICE(expr, offs, sizes)
#endif

// }}}
