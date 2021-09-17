static extent_t *
extent_lock_from_addr(tsdn_t *tsdn, rtree_ctx_t *rtree_ctx, void *addr) {
	extent_t *ret = NULL;
	rtree_leaf_elm_t *elm = rtree_leaf_elm_lookup(tsdn, &extents_rtree,
	    rtree_ctx, (uintptr_t)addr, false, false);
	if (elm == NULL) {
		return NULL;
	}
	lock_result_t lock_result;
	do {
		lock_result = extent_rtree_leaf_elm_try_lock(tsdn, elm, &ret);
	} while (lock_result == lock_result_failure);
	return ret;
}
