static rtree_leaf_elm_t *
rtree_leaf_alloc_impl(tsdn_t *tsdn, rtree_t *rtree, size_t nelms) {
	return (rtree_leaf_elm_t *)base_alloc(tsdn, b0get(), nelms *
	    sizeof(rtree_leaf_elm_t), CACHELINE);
}
