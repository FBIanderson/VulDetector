static void
rtree_leaf_dalloc_intercept(tsdn_t *tsdn, rtree_t *rtree,
    rtree_leaf_elm_t *leaf) {
	if (rtree != &test_rtree) {
		rtree_leaf_dalloc_orig(tsdn, rtree, leaf);
		return;
	}

	free(leaf);
}
