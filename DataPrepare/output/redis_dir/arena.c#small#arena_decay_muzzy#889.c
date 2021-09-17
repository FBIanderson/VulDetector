static bool
arena_decay_muzzy(tsdn_t *tsdn, arena_t *arena, bool is_background_thread,
    bool all) {
	return arena_decay_impl(tsdn, arena, &arena->decay_muzzy,
	    &arena->extents_muzzy, is_background_thread, all);
}
