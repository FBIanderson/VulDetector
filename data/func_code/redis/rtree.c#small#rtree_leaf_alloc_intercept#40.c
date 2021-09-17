static rtree_leaf_elm_t *
rtree_leaf_alloc_intercept(tsdn_t *tsdn, rtree_t *rtree, size_t nelms) {
	rtree_leaf_elm_t *leaf;

	if (rtree != &test_rtree) {
		return rtree_leaf_alloc_orig(tsdn, rtree, nelms);
	}

	malloc_mutex_unlock(tsdn, &rtree->init_lock);
	leaf = (rtree_leaf_elm_t *)calloc(nelms, sizeof(rtree_leaf_elm_t));
	assert_ptr_not_null(leaf, "Unexpected calloc() failure");
	malloc_mutex_lock(tsdn, &rtree->init_lock);

	return leaf;
}
