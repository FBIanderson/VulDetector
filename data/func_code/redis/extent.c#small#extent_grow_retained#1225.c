static extent_t *
extent_grow_retained(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, size_t size, size_t pad, size_t alignment,
    bool slab, szind_t szind, bool *zero, bool *commit) {
	malloc_mutex_assert_owner(tsdn, &arena->extent_grow_mtx);
	assert(pad == 0 || !slab);
	assert(!*zero || !slab);

	size_t esize = size + pad;
	size_t alloc_size_min = esize + PAGE_CEILING(alignment) - PAGE;
	/* Beware size_t wrap-around. */
	if (alloc_size_min < esize) {
		goto label_err;
	}
	/*
	 * Find the next extent size in the series that would be large enough to
	 * satisfy this request.
	 */
	pszind_t egn_skip = 0;
	size_t alloc_size = sz_pind2sz(arena->extent_grow_next + egn_skip);
	while (alloc_size < alloc_size_min) {
		egn_skip++;
		if (arena->extent_grow_next + egn_skip == NPSIZES) {
			/* Outside legal range. */
			goto label_err;
		}
		assert(arena->extent_grow_next + egn_skip < NPSIZES);
		alloc_size = sz_pind2sz(arena->extent_grow_next + egn_skip);
	}

	extent_t *extent = extent_alloc(tsdn, arena);
	if (extent == NULL) {
		goto label_err;
	}
	bool zeroed = false;
	bool committed = false;

	void *ptr;
	if (*r_extent_hooks == &extent_hooks_default) {
		ptr = extent_alloc_default_impl(tsdn, arena, NULL,
		    alloc_size, PAGE, &zeroed, &committed);
	} else {
		extent_hook_pre_reentrancy(tsdn, arena);
		ptr = (*r_extent_hooks)->alloc(*r_extent_hooks, NULL,
		    alloc_size, PAGE, &zeroed, &committed,
		    arena_ind_get(arena));
		extent_hook_post_reentrancy(tsdn);
	}

	extent_init(extent, arena, ptr, alloc_size, false, NSIZES,
	    arena_extent_sn_next(arena), extent_state_active, zeroed,
	    committed, true);
	if (ptr == NULL) {
		extent_dalloc(tsdn, arena, extent);
		goto label_err;
	}

	if (extent_register_no_gdump_add(tsdn, extent)) {
		extents_leak(tsdn, arena, r_extent_hooks,
		    &arena->extents_retained, extent, true);
		goto label_err;
	}

	if (extent_zeroed_get(extent) && extent_committed_get(extent)) {
		*zero = true;
	}
	if (extent_committed_get(extent)) {
		*commit = true;
	}

	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	extent_t *lead;
	extent_t *trail;
	extent_t *to_leak;
	extent_t *to_salvage;
	extent_split_interior_result_t result = extent_split_interior(
	    tsdn, arena, r_extent_hooks, rtree_ctx, &extent, &lead, &trail,
	    &to_leak, &to_salvage, NULL, size, pad, alignment, slab, szind,
	    true);

	if (result == extent_split_interior_ok) {
		if (lead != NULL) {
			extent_record(tsdn, arena, r_extent_hooks,
			    &arena->extents_retained, lead, true);
		}
		if (trail != NULL) {
			extent_record(tsdn, arena, r_extent_hooks,
			    &arena->extents_retained, trail, true);
		}
	} else {
		/*
		 * We should have allocated a sufficiently large extent; the
		 * cant_alloc case should not occur.
		 */
		assert(result == extent_split_interior_error);
		if (to_salvage != NULL) {
			if (config_prof) {
				extent_gdump_add(tsdn, to_salvage);
			}
			extent_record(tsdn, arena, r_extent_hooks,
			    &arena->extents_retained, to_salvage, true);
		}
		if (to_leak != NULL) {
			extent_deregister_no_gdump_sub(tsdn, to_leak);
			extents_leak(tsdn, arena, r_extent_hooks,
			    &arena->extents_retained, to_leak, true);
		}
		goto label_err;
	}

	if (*commit && !extent_committed_get(extent)) {
		if (extent_commit_impl(tsdn, arena, r_extent_hooks, extent, 0,
		    extent_size_get(extent), true)) {
			extent_record(tsdn, arena, r_extent_hooks,
			    &arena->extents_retained, extent, true);
			goto label_err;
		}
		extent_zeroed_set(extent, true);
	}

	/*
	 * Increment extent_grow_next if doing so wouldn't exceed the allowed
	 * range.
	 */
	if (arena->extent_grow_next + egn_skip + 1 <=
	    arena->retain_grow_limit) {
		arena->extent_grow_next += egn_skip + 1;
	} else {
		arena->extent_grow_next = arena->retain_grow_limit;
	}
	/* All opportunities for failure are past. */
	malloc_mutex_unlock(tsdn, &arena->extent_grow_mtx);

	if (config_prof) {
		/* Adjust gdump stats now that extent is final size. */
		extent_gdump_add(tsdn, extent);
	}
	if (pad != 0) {
		extent_addr_randomize(tsdn, extent, alignment);
	}
	if (slab) {
		rtree_ctx_t rtree_ctx_fallback;
		rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn,
		    &rtree_ctx_fallback);

		extent_slab_set(extent, true);
		extent_interior_register(tsdn, rtree_ctx, extent, szind);
	}
	if (*zero && !extent_zeroed_get(extent)) {
		void *addr = extent_base_get(extent);
		size_t size = extent_size_get(extent);
		if (pages_purge_forced(addr, size)) {
			memset(addr, 0, size);
		}
	}

	return extent;
label_err:
	malloc_mutex_unlock(tsdn, &arena->extent_grow_mtx);
	return NULL;
}
