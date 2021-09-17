void *
large_ralloc(tsdn_t *tsdn, arena_t *arena, extent_t *extent, size_t usize,
    size_t alignment, bool zero, tcache_t *tcache) {
	size_t oldusize = extent_usize_get(extent);

	/* The following should have been caught by callers. */
	assert(usize > 0 && usize <= LARGE_MAXCLASS);
	/* Both allocation sizes must be large to avoid a move. */
	assert(oldusize >= LARGE_MINCLASS && usize >= LARGE_MINCLASS);

	/* Try to avoid moving the allocation. */
	if (!large_ralloc_no_move(tsdn, extent, usize, usize, zero)) {
		return extent_addr_get(extent);
	}

	/*
	 * usize and old size are different enough that we need to use a
	 * different size class.  In that case, fall back to allocating new
	 * space and copying.
	 */
	void *ret = large_ralloc_move_helper(tsdn, arena, usize, alignment,
	    zero);
	if (ret == NULL) {
		return NULL;
	}

	size_t copysize = (usize < oldusize) ? usize : oldusize;
	memcpy(ret, extent_addr_get(extent), copysize);
	isdalloct(tsdn, extent_addr_get(extent), oldusize, tcache, NULL, true);
	return ret;
}
