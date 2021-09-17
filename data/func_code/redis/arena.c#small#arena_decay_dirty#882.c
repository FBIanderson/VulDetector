static bool
arena_decay_dirty(tsdn_t *tsdn, arena_t *arena, bool is_background_thread,
    bool all) {
	return arena_decay_impl(tsdn, arena, &arena->decay_dirty,
	    &arena->extents_dirty, is_background_thread, all);
}
