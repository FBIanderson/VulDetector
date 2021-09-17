static void
arena_nactive_add(arena_t *arena, size_t add_pages) {
	atomic_fetch_add_zu(&arena->nactive, add_pages, ATOMIC_RELAXED);
}
