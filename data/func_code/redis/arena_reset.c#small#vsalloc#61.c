static size_t
vsalloc(tsdn_t *tsdn, const void *ptr) {
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	extent_t *extent;
	szind_t szind;
	if (rtree_extent_szind_read(tsdn, &extents_rtree, rtree_ctx,
	    (uintptr_t)ptr, false, &extent, &szind)) {
		return 0;
	}

	if (extent == NULL) {
		return 0;
	}
	if (extent_state_get(extent) != extent_state_active) {
		return 0;
	}

	if (szind == NSIZES) {
		return 0;
	}

	return sz_index2size(szind);
}
