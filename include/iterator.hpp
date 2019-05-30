// iterator {{{

template<typename T, typename U=typename T::iterator_category>
true_type HAS_ITERATOR_CATEGORY_HELPER(int);
template<typename T>
false_type HAS_ITERATOR_CATEGORY_HELPER(long);

template<typename T>
struct HAS_ITERATOR_CATEGORY : decltype(HAS_ITERATOR_CATEGORY_HELPER<T>(0)) {};

template<typename T, typename U, bool=HAS_ITERATOR_CATEGORY<iterator_traits<T>>::value>
struct HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO
    : integral_constant<bool,is_convertible<typename iterator_traits<T>::iterator_category,U>::value> {};

template<typename T, typename U>
struct HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO<T,U,false> : false_type {};

template<typename T>
struct IS_INPUT_ITERATOR : public HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO<T,input_iterator_tag> {};
template<typename T>
struct IS_FORWARD_ITERATOR : public HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO<T,forward_iterator_tag> {};
template<typename T>
struct IS_BIDIRECTIONAL_ITERATOR : public HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO<T,bidirectional_iterator_tag> {};
template<typename T>
struct IS_RANDOM_ACCESS_ITERATOR : public HAS_ITERATOR_CATEGORY_CONVERTIBLE_TO<T,random_access_iterator_tag> {};

// }}}
