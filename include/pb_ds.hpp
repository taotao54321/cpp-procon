// pb_ds {{{

template<typename T, typename Comp=less<T>>
using RbTreeSet = pbds::tree<T,pbds::null_type,Comp,pbds::rb_tree_tag,pbds::tree_order_statistics_node_update>;

template<typename K, typename V, typename Comp=less<K>>
using RbTreeMap = pbds::tree<K,V,Comp,pbds::rb_tree_tag,pbds::tree_order_statistics_node_update>;

template<
    typename T, typename Hash=procon_hash<T>, typename Eq=equal_to<T>,
    typename Comb=pbds::direct_mask_range_hashing<>,
    typename ResizePolicy=pbds::hash_standard_resize_policy<>,
    bool StoreHash=false
>
using CcHashSet = pbds::cc_hash_table<T,pbds::null_type,Hash,Eq,Comb,ResizePolicy,StoreHash>;

template<
    typename K, typename V, typename Hash=procon_hash<K>, typename Eq=equal_to<K>,
    typename Comb=pbds::direct_mask_range_hashing<>,
    typename ResizePolicy=pbds::hash_standard_resize_policy<>,
    bool StoreHash=false
>
using CcHashMap = pbds::cc_hash_table<K,V,Hash,Eq,Comb,ResizePolicy,StoreHash>;

template<
    typename T, typename Hash=procon_hash<T>, typename Eq=equal_to<T>,
    typename Comb=pbds::direct_mask_range_hashing<>,
    typename ResizePolicy=pbds::hash_standard_resize_policy<>,
    bool StoreHash=false
>
auto make_cc_hash_set(i64 cap, f32 load_max=0.25) {
    using SizePolicy    = typename ResizePolicy::size_policy;
    using TriggerPolicy = typename ResizePolicy::trigger_policy;

    ResizePolicy rp(SizePolicy(cap), TriggerPolicy(0.0,load_max));
    CcHashSet<T,Hash,Eq,Comb,ResizePolicy,StoreHash> res;
    return res;
}

template<
    typename K, typename V, typename Hash=procon_hash<K>, typename Eq=equal_to<K>,
    typename Comb=pbds::direct_mask_range_hashing<>,
    typename ResizePolicy=pbds::hash_standard_resize_policy<>,
    bool StoreHash=false
>
auto make_cc_hash_map(i64 cap, f32 load_max=0.25) {
    using SizePolicy    = typename ResizePolicy::size_policy;
    using TriggerPolicy = typename ResizePolicy::trigger_policy;

    ResizePolicy rp(SizePolicy(cap), TriggerPolicy(0.0,load_max));
    CcHashMap<K,V,Hash,Eq,Comb,ResizePolicy,StoreHash> res;
    return res;
}

template<
    typename T, typename Hash=procon_hash<T>, typename Eq=equal_to<T>,
    typename Comb=pbds::direct_mask_range_hashing<>,
    typename Probe=pbds::linear_probe_fn<>,
    typename ResizePolicy=pbds::hash_standard_resize_policy<>,
    bool StoreHash=false
>
using GpHashSet = pbds::gp_hash_table<T,pbds::null_type,Hash,Eq,Comb,Probe,ResizePolicy,StoreHash>;

template<
    typename K, typename V, typename Hash=procon_hash<K>, typename Eq=equal_to<K>,
    typename Comb=pbds::direct_mask_range_hashing<>,
    typename Probe=pbds::linear_probe_fn<>,
    typename ResizePolicy=pbds::hash_standard_resize_policy<>,
    bool StoreHash=false
>
using GpHashMap = pbds::gp_hash_table<K,V,Hash,Eq,Comb,Probe,ResizePolicy,StoreHash>;

template<
    typename T, typename Hash=procon_hash<T>, typename Eq=equal_to<T>,
    typename Comb=pbds::direct_mask_range_hashing<>,
    typename Probe=pbds::linear_probe_fn<>,
    typename ResizePolicy=pbds::hash_standard_resize_policy<>,
    bool StoreHash=false
>
auto make_gp_hash_set(i64 cap, f32 load_max=0.25) {
    using SizePolicy    = typename ResizePolicy::size_policy;
    using TriggerPolicy = typename ResizePolicy::trigger_policy;

    ResizePolicy rp(SizePolicy(cap), TriggerPolicy(0.0,load_max));
    GpHashSet<T,Hash,Eq,Comb,Probe,ResizePolicy,StoreHash> res;
    return res;
}

template<
    typename K, typename V, typename Hash=procon_hash<K>, typename Eq=equal_to<K>,
    typename Comb=pbds::direct_mask_range_hashing<>,
    typename Probe=pbds::linear_probe_fn<>,
    typename ResizePolicy=pbds::hash_standard_resize_policy<>,
    bool StoreHash=false
>
auto make_gp_hash_map(i64 cap, f32 load_max=0.25) {
    using SizePolicy    = typename ResizePolicy::size_policy;
    using TriggerPolicy = typename ResizePolicy::trigger_policy;

    ResizePolicy rp(SizePolicy(cap), TriggerPolicy(0.0,load_max));
    GpHashMap<K,V,Hash,Eq,Comb,Probe,ResizePolicy,StoreHash> res;
    return res;
}

// }}}
