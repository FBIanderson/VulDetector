void
arena_prof_promote(tsdn_t *tsdn, const void *ptr, size_t usize) {
	cassert(config_prof);
	assert(ptr != NULL);
	assert(isalloc(tsdn, ptr) == LARGE_MINCLASS);
	assert(usize <= SMALL_MAXCLASS);

	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	extent_t *extent = rtree_extent_read(tsdn, &extents_rtree, rtree_ctx,
	    (uintptr_t)ptr, true);
	arena_t *arena = extent_arena_get(extent);

	szind_t szind = sz_size2index(usize);
	extent_szind_set(extent, szind);
	rtree_szind_slab_update(tsdn, &extents_rtree, rtree_ctx, (uintptr_t)ptr,
	    szind, false);

	prof_accum_cancel(tsdn, &arena->prof_accum, usize);

	assert(isalloc(tsdn, ptr) == usize);
}
