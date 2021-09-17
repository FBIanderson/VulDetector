static void
rtree_leaf_dalloc_impl(tsdn_t *tsdn, rtree_t *rtree, rtree_leaf_elm_t *leaf) {
	/* Leaves are never deleted during normal operation. */
	not_reached();
}
