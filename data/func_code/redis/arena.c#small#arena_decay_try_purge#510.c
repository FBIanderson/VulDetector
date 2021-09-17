static void
arena_decay_try_purge(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    extents_t *extents, size_t current_npages, size_t npages_limit,
    bool is_background_thread) {
	if (current_npages > npages_limit) {
		arena_decay_to_limit(tsdn, arena, decay, extents, false,
		    npages_limit, current_npages - npages_limit,
		    is_background_thread);
	}
}
