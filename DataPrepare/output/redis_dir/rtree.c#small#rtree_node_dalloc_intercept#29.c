static void
rtree_node_dalloc_intercept(tsdn_t *tsdn, rtree_t *rtree,
    rtree_node_elm_t *node) {
	if (rtree != &test_rtree) {
		rtree_node_dalloc_orig(tsdn, rtree, node);
		return;
	}

	free(node);
}
