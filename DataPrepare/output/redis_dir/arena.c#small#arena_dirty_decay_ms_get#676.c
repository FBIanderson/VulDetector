ssize_t
arena_dirty_decay_ms_get(arena_t *arena) {
	return arena_decay_ms_get(&arena->decay_dirty);
}
