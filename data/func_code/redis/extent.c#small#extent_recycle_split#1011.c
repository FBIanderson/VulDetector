static extent_t *
extent_recycle_split(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, rtree_ctx_t *rtree_ctx, extents_t *extents,
    void *new_addr, size_t size, size_t pad, size_t alignment, bool slab,
    szind_t szind, extent_t *extent, bool growing_retained) {
	extent_t *lead;
	extent_t *trail;
	extent_t *to_leak;
	extent_t *to_salvage;

	extent_split_interior_result_t result = extent_split_interior(
	    tsdn, arena, r_extent_hooks, rtree_ctx, &extent, &lead, &trail,
	    &to_leak, &to_salvage, new_addr, size, pad, alignment, slab, szind,
	    growing_retained);

	if (result == extent_split_interior_ok) {
		if (lead != NULL) {
			extent_deactivate(tsdn, arena, extents, lead);
		}
		if (trail != NULL) {
			extent_deactivate(tsdn, arena, extents, trail);
		}
		return extent;
	} else {
		/*
		 * We should have picked an extent that was large enough to
		 * fulfill our allocation request.
		 */
		assert(result == extent_split_interior_error);
		if (to_salvage != NULL) {
			extent_deregister(tsdn, to_salvage);
		}
		if (to_leak != NULL) {
			void *leak = extent_base_get(to_leak);
			extent_deregister_no_gdump_sub(tsdn, to_leak);
			extents_leak(tsdn, arena, r_extent_hooks, extents,
			    to_leak, growing_retained);
			assert(extent_lock_from_addr(tsdn, rtree_ctx, leak)
			    == NULL);
		}
		return NULL;
	}
	unreachable();
}
