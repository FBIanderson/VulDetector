static void
extent_record(tsdn_t *tsdn, arena_t *arena, extent_hooks_t **r_extent_hooks,
    extents_t *extents, extent_t *extent, bool growing_retained) {
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	assert((extents_state_get(extents) != extent_state_dirty &&
	    extents_state_get(extents) != extent_state_muzzy) ||
	    !extent_zeroed_get(extent));

	malloc_mutex_lock(tsdn, &extents->mtx);
	extent_hooks_assure_initialized(arena, r_extent_hooks);

	extent_szind_set(extent, NSIZES);
	if (extent_slab_get(extent)) {
		extent_interior_deregister(tsdn, rtree_ctx, extent);
		extent_slab_set(extent, false);
	}

	assert(rtree_extent_read(tsdn, &extents_rtree, rtree_ctx,
	    (uintptr_t)extent_base_get(extent), true) == extent);

	if (!extents->delay_coalesce) {
		extent = extent_try_coalesce(tsdn, arena, r_extent_hooks,
		    rtree_ctx, extents, extent, NULL, growing_retained);
	} else if (extent_size_get(extent) >= LARGE_MINCLASS) {
		/* Always coalesce large extents eagerly. */
		bool coalesced;
		size_t prev_size;
		do {
			prev_size = extent_size_get(extent);
			assert(extent_state_get(extent) == extent_state_active);
			extent = extent_try_coalesce(tsdn, arena,
			    r_extent_hooks, rtree_ctx, extents, extent,
			    &coalesced, growing_retained);
		} while (coalesced &&
		    extent_size_get(extent) >= prev_size + LARGE_MINCLASS);
	}
	extent_deactivate_locked(tsdn, arena, extents, extent);

	malloc_mutex_unlock(tsdn, &extents->mtx);
}
