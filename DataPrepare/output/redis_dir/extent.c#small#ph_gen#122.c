ph_gen(UNUSED, extent_avail_, extent_tree_t, extent_t, ph_link,
    extent_esnead_comp)

typedef enum {
	lock_result_success,
	lock_result_failure,
	lock_result_no_extent
} lock_result_t;

static lock_result_t
extent_rtree_leaf_elm_try_lock(tsdn_t *tsdn, rtree_leaf_elm_t *elm,
    extent_t **result) {
	extent_t *extent1 = rtree_leaf_elm_extent_read(tsdn, &extents_rtree,
	    elm, true);

	if (extent1 == NULL) {
		return lock_result_no_extent;
	}
	/*
	 * It's possible that the extent changed out from under us, and with it
	 * the leaf->extent mapping.  We have to recheck while holding the lock.
	 */
	extent_lock(tsdn, extent1);
	extent_t *extent2 = rtree_leaf_elm_extent_read(tsdn,
	    &extents_rtree, elm, true);

	if (extent1 == extent2) {
		*result = extent1;
		return lock_result_success;
	} else {
		extent_unlock(tsdn, extent1);
		return lock_result_failure;
	}
}
