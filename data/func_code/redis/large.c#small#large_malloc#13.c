void *
large_malloc(tsdn_t *tsdn, arena_t *arena, size_t usize, bool zero) {
	assert(usize == sz_s2u(usize));

	return large_palloc(tsdn, arena, usize, CACHELINE, zero);
}
