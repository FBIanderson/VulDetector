static extent_split_interior_result_t
extent_split_interior(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, rtree_ctx_t *rtree_ctx,
    /* The result of splitting, in case of success. */
    extent_t **extent, extent_t **lead, extent_t **trail,
    /* The mess to clean up, in case of error. */
    extent_t **to_leak, extent_t **to_salvage,
    void *new_addr, size_t size, size_t pad, size_t alignment, bool slab,
    szind_t szind, bool growing_retained) {
	size_t esize = size + pad;
	size_t leadsize = ALIGNMENT_CEILING((uintptr_t)extent_base_get(*extent),
	    PAGE_CEILING(alignment)) - (uintptr_t)extent_base_get(*extent);
	assert(new_addr == NULL || leadsize == 0);
	if (extent_size_get(*extent) < leadsize + esize) {
		return extent_split_interior_cant_alloc;
	}
	size_t trailsize = extent_size_get(*extent) - leadsize - esize;

	*lead = NULL;
	*trail = NULL;
	*to_leak = NULL;
	*to_salvage = NULL;

	/* Split the lead. */
	if (leadsize != 0) {
		*lead = *extent;
		*extent = extent_split_impl(tsdn, arena, r_extent_hooks,
		    *lead, leadsize, NSIZES, false, esize + trailsize, szind,
		    slab, growing_retained);
		if (*extent == NULL) {
			*to_leak = *lead;
			*lead = NULL;
			return extent_split_interior_error;
		}
	}

	/* Split the trail. */
	if (trailsize != 0) {
		*trail = extent_split_impl(tsdn, arena, r_extent_hooks, *extent,
		    esize, szind, slab, trailsize, NSIZES, false,
		    growing_retained);
		if (*trail == NULL) {
			*to_leak = *extent;
			*to_salvage = *lead;
			*lead = NULL;
			*extent = NULL;
			return extent_split_interior_error;
		}
	}

	if (leadsize == 0 && trailsize == 0) {
		/*
		 * Splitting causes szind to be set as a side effect, but no
		 * splitting occurred.
		 */
		extent_szind_set(*extent, szind);
		if (szind != NSIZES) {
			rtree_szind_slab_update(tsdn, &extents_rtree, rtree_ctx,
			    (uintptr_t)extent_addr_get(*extent), szind, slab);
			if (slab && extent_size_get(*extent) > PAGE) {
				rtree_szind_slab_update(tsdn, &extents_rtree,
				    rtree_ctx,
				    (uintptr_t)extent_past_get(*extent) -
				    (uintptr_t)PAGE, szind, slab);
			}
		}
	}

	return extent_split_interior_ok;
}
