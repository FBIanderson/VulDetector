static void
rtree_node_dalloc_impl(tsdn_t *tsdn, rtree_t *rtree, rtree_node_elm_t *node) {
	/* Nodes are never deleted during normal operation. */
	not_reached();
}
