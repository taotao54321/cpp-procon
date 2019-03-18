// {{{ debug

template<typename T>
ostream& operator<<(ostream& out, const deque<T>& deq) {
    return out << "deque[" << ALL(JOIN, deq, ", ") << "]";
}

// }}}
