static bool
large_ralloc_no_move_expand(tsdn_t *tsdn, extent_t *extent, size_t usize,
    bool zero) {
	arena_t *arena = extent_arena_get(extent);
	size_t oldusize = extent_usize_get(extent);
	extent_hooks_t *extent_hooks = extent_hooks_get(arena);
	size_t trailsize = usize - oldusize;

	if (extent_hooks->merge == NULL) {
		return true;
	}

	if (config_fill && unlikely(opt_zero)) {
		zero = true;
	}
	/*
	 * Copy zero into is_zeroed_trail and pass the copy when allocating the
	 * extent, so that it is possible to make correct junk/zero fill
	 * decisions below, even if is_zeroed_trail ends up true when zero is
	 * false.
	 */
	bool is_zeroed_trail = zero;
	bool commit = true;
	extent_t *trail;
	bool new_mapping;
	if ((trail = extents_alloc(tsdn, arena, &extent_hooks,
	    &arena->extents_dirty, extent_past_get(extent), trailsize, 0,
	    CACHELINE, false, NSIZES, &is_zeroed_trail, &commit)) != NULL
	    || (trail = extents_alloc(tsdn, arena, &extent_hooks,
	    &arena->extents_muzzy, extent_past_get(extent), trailsize, 0,
	    CACHELINE, false, NSIZES, &is_zeroed_trail, &commit)) != NULL) {
		if (config_stats) {
			new_mapping = false;
		}
	} else {
		if ((trail = extent_alloc_wrapper(tsdn, arena, &extent_hooks,
		    extent_past_get(extent), trailsize, 0, CACHELINE, false,
		    NSIZES, &is_zeroed_trail, &commit)) == NULL) {
			return true;
		}
		if (config_stats) {
			new_mapping = true;
		}
	}

	if (extent_merge_wrapper(tsdn, arena, &extent_hooks, extent, trail)) {
		extent_dalloc_wrapper(tsdn, arena, &extent_hooks, trail);
		return true;
	}
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);
	szind_t szind = sz_size2index(usize);
	extent_szind_set(extent, szind);
	rtree_szind_slab_update(tsdn, &extents_rtree, rtree_ctx,
	    (uintptr_t)extent_addr_get(extent), szind, false);

	if (config_stats && new_mapping) {
		arena_stats_mapped_add(tsdn, &arena->stats, trailsize);
	}

	if (zero) {
		if (config_cache_oblivious) {
			/*
			 * Zero the trailing bytes of the original allocation's
			 * last page, since they are in an indeterminate state.
			 * There will always be trailing bytes, because ptr's
			 * offset from the beginning of the extent is a multiple
			 * of CACHELINE in [0 .. PAGE).
			 */
			void *zbase = (void *)
			    ((uintptr_t)extent_addr_get(extent) + oldusize);
			void *zpast = PAGE_ADDR2BASE((void *)((uintptr_t)zbase +
			    PAGE));
			size_t nzero = (uintptr_t)zpast - (uintptr_t)zbase;
			assert(nzero > 0);
			memset(zbase, 0, nzero);
		}
		assert(is_zeroed_trail);
	} else if (config_fill && unlikely(opt_junk_alloc)) {
		memset((void *)((uintptr_t)extent_addr_get(extent) + oldusize),
		    JEMALLOC_ALLOC_JUNK, usize - oldusize);
	}

	arena_extent_ralloc_large_expand(tsdn, arena, extent, oldusize);

	return false;
}
