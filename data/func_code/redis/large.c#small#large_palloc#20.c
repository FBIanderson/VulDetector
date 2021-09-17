void *
large_palloc(tsdn_t *tsdn, arena_t *arena, size_t usize, size_t alignment,
    bool zero) {
	size_t ausize;
	extent_t *extent;
	bool is_zeroed;
	UNUSED bool idump JEMALLOC_CC_SILENCE_INIT(false);

	assert(!tsdn_null(tsdn) || arena != NULL);

	ausize = sz_sa2u(usize, alignment);
	if (unlikely(ausize == 0 || ausize > LARGE_MAXCLASS)) {
		return NULL;
	}

	if (config_fill && unlikely(opt_zero)) {
		zero = true;
	}
	/*
	 * Copy zero into is_zeroed and pass the copy when allocating the
	 * extent, so that it is possible to make correct junk/zero fill
	 * decisions below, even if is_zeroed ends up true when zero is false.
	 */
	is_zeroed = zero;
	if (likely(!tsdn_null(tsdn))) {
		arena = arena_choose(tsdn_tsd(tsdn), arena);
	}
	if (unlikely(arena == NULL) || (extent = arena_extent_alloc_large(tsdn,
	    arena, usize, alignment, &is_zeroed)) == NULL) {
		return NULL;
	}

	/* See comments in arena_bin_slabs_full_insert(). */
	if (!arena_is_auto(arena)) {
		/* Insert extent into large. */
		malloc_mutex_lock(tsdn, &arena->large_mtx);
		extent_list_append(&arena->large, extent);
		malloc_mutex_unlock(tsdn, &arena->large_mtx);
	}
	if (config_prof && arena_prof_accum(tsdn, arena, usize)) {
		prof_idump(tsdn);
	}

	if (zero) {
		assert(is_zeroed);
	} else if (config_fill && unlikely(opt_junk_alloc)) {
		memset(extent_addr_get(extent), JEMALLOC_ALLOC_JUNK,
		    extent_usize_get(extent));
	}

	arena_decay_tick(tsdn, arena);
	return extent_addr_get(extent);
}
