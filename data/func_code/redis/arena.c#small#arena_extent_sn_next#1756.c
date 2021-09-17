size_t
arena_extent_sn_next(arena_t *arena) {
	return atomic_fetch_add_zu(&arena->extent_sn_next, 1, ATOMIC_RELAXED);
}
