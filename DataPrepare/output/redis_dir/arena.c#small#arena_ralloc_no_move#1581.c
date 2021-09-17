bool
arena_ralloc_no_move(tsdn_t *tsdn, void *ptr, size_t oldsize, size_t size,
    size_t extra, bool zero) {
	/* Calls with non-zero extra had to clamp extra. */
	assert(extra == 0 || size + extra <= LARGE_MAXCLASS);

	if (unlikely(size > LARGE_MAXCLASS)) {
		return true;
	}

	extent_t *extent = iealloc(tsdn, ptr);
	size_t usize_min = sz_s2u(size);
	size_t usize_max = sz_s2u(size + extra);
	if (likely(oldsize <= SMALL_MAXCLASS && usize_min <= SMALL_MAXCLASS)) {
		/*
		 * Avoid moving the allocation if the size class can be left the
		 * same.
		 */
		assert(bin_infos[sz_size2index(oldsize)].reg_size ==
		    oldsize);
		if ((usize_max > SMALL_MAXCLASS || sz_size2index(usize_max) !=
		    sz_size2index(oldsize)) && (size > oldsize || usize_max <
		    oldsize)) {
			return true;
		}

		arena_decay_tick(tsdn, extent_arena_get(extent));
		return false;
	} else if (oldsize >= LARGE_MINCLASS && usize_max >= LARGE_MINCLASS) {
		return large_ralloc_no_move(tsdn, extent, usize_min, usize_max,
		    zero);
	}

	return true;
}
