void
arena_decay(tsdn_t *tsdn, arena_t *arena, bool is_background_thread, bool all) {
	if (arena_decay_dirty(tsdn, arena, is_background_thread, all)) {
		return;
	}
	arena_decay_muzzy(tsdn, arena, is_background_thread, all);
}
