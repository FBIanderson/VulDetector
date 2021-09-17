static rtree_node_elm_t *
rtree_node_alloc_impl(tsdn_t *tsdn, rtree_t *rtree, size_t nelms) {
	return (rtree_node_elm_t *)base_alloc(tsdn, b0get(), nelms *
	    sizeof(rtree_node_elm_t), CACHELINE);
}
