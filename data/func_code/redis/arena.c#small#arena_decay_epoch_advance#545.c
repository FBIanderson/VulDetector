static void
arena_decay_epoch_advance(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    extents_t *extents, const nstime_t *time, bool is_background_thread) {
	size_t current_npages = extents_npages_get(extents);
	arena_decay_epoch_advance_helper(decay, time, current_npages);

	size_t npages_limit = arena_decay_backlog_npages_limit(decay);
	/* We may unlock decay->mtx when try_purge(). Finish logging first. */
	decay->nunpurged = (npages_limit > current_npages) ? npages_limit :
	    current_npages;

	if (!background_thread_enabled() || is_background_thread) {
		arena_decay_try_purge(tsdn, arena, decay, extents,
		    current_npages, npages_limit, is_background_thread);
	}
}
