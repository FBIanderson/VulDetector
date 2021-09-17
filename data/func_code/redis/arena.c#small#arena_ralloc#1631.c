void *
arena_ralloc(tsdn_t *tsdn, arena_t *arena, void *ptr, size_t oldsize,
    size_t size, size_t alignment, bool zero, tcache_t *tcache) {
	size_t usize = sz_s2u(size);
	if (unlikely(usize == 0 || size > LARGE_MAXCLASS)) {
		return NULL;
	}

	if (likely(usize <= SMALL_MAXCLASS)) {
		/* Try to avoid moving the allocation. */
		if (!arena_ralloc_no_move(tsdn, ptr, oldsize, usize, 0, zero)) {
			return ptr;
		}
	}

	if (oldsize >= LARGE_MINCLASS && usize >= LARGE_MINCLASS) {
		return large_ralloc(tsdn, arena, iealloc(tsdn, ptr), usize,
		    alignment, zero, tcache);
	}

	/*
	 * size and oldsize are different enough that we need to move the
	 * object.  In that case, fall back to allocating new space and copying.
	 */
	void *ret = arena_ralloc_move_helper(tsdn, arena, usize, alignment,
	    zero, tcache);
	if (ret == NULL) {
		return NULL;
	}

	/*
	 * Junk/zero-filling were already done by
	 * ipalloc()/arena_malloc().
	 */

	size_t copysize = (usize < oldsize) ? usize : oldsize;
	memcpy(ret, ptr, copysize);
	isdalloct(tsdn, ptr, oldsize, tcache, NULL, true);
	return ret;
}
