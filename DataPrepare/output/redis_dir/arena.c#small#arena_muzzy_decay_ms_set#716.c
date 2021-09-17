bool
arena_muzzy_decay_ms_set(tsdn_t *tsdn, arena_t *arena,
    ssize_t decay_ms) {
	return arena_decay_ms_set(tsdn, arena, &arena->decay_muzzy,
	    &arena->extents_muzzy, decay_ms);
}
