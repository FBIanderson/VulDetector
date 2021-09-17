static void
arena_nactive_sub(arena_t *arena, size_t sub_pages) {
	assert(atomic_load_zu(&arena->nactive, ATOMIC_RELAXED) >= sub_pages);
	atomic_fetch_sub_zu(&arena->nactive, sub_pages, ATOMIC_RELAXED);
}
