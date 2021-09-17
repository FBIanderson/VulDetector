static size_t
arena_prof_demote(tsdn_t *tsdn, extent_t *extent, const void *ptr) {
	cassert(config_prof);
	assert(ptr != NULL);

	extent_szind_set(extent, NBINS);
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);
	rtree_szind_slab_update(tsdn, &extents_rtree, rtree_ctx, (uintptr_t)ptr,
	    NBINS, false);

	assert(isalloc(tsdn, ptr) == LARGE_MINCLASS);

	return LARGE_MINCLASS;
}
