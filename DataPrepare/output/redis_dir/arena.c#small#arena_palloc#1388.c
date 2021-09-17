void *
arena_palloc(tsdn_t *tsdn, arena_t *arena, size_t usize, size_t alignment,
    bool zero, tcache_t *tcache) {
	void *ret;

	if (usize <= SMALL_MAXCLASS && (alignment < PAGE || (alignment == PAGE
	    && (usize & PAGE_MASK) == 0))) {
		/* Small; alignment doesn't require special slab placement. */
		ret = arena_malloc(tsdn, arena, usize, sz_size2index(usize),
		    zero, tcache, true);
	} else {
		if (likely(alignment <= CACHELINE)) {
			ret = large_malloc(tsdn, arena, usize, zero);
		} else {
			ret = large_palloc(tsdn, arena, usize, alignment, zero);
		}
	}
	return ret;
}
