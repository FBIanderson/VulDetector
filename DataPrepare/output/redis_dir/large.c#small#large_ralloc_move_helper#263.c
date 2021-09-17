static void *
large_ralloc_move_helper(tsdn_t *tsdn, arena_t *arena, size_t usize,
    size_t alignment, bool zero) {
	if (alignment <= CACHELINE) {
		return large_malloc(tsdn, arena, usize, zero);
	}
	return large_palloc(tsdn, arena, usize, alignment, zero);
}
