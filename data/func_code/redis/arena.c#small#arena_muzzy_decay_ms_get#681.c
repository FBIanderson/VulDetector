ssize_t
arena_muzzy_decay_ms_get(arena_t *arena) {
	return arena_decay_ms_get(&arena->decay_muzzy);
}
