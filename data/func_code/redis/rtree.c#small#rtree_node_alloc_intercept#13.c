static rtree_node_elm_t *
rtree_node_alloc_intercept(tsdn_t *tsdn, rtree_t *rtree, size_t nelms) {
	rtree_node_elm_t *node;

	if (rtree != &test_rtree) {
		return rtree_node_alloc_orig(tsdn, rtree, nelms);
	}

	malloc_mutex_unlock(tsdn, &rtree->init_lock);
	node = (rtree_node_elm_t *)calloc(nelms, sizeof(rtree_node_elm_t));
	assert_ptr_not_null(node, "Unexpected calloc() failure");
	malloc_mutex_lock(tsdn, &rtree->init_lock);

	return node;
}
