bool
arena_dirty_decay_ms_set(tsdn_t *tsdn, arena_t *arena,
    ssize_t decay_ms) {
	return arena_decay_ms_set(tsdn, arena, &arena->decay_dirty,
	    &arena->extents_dirty, decay_ms);
}
