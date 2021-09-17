static bool
arena_decay_impl(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    extents_t *extents, bool is_background_thread, bool all) {
	if (all) {
		malloc_mutex_lock(tsdn, &decay->mtx);
		arena_decay_to_limit(tsdn, arena, decay, extents, all, 0,
		    extents_npages_get(extents), is_background_thread);
		malloc_mutex_unlock(tsdn, &decay->mtx);

		return false;
	}

	if (malloc_mutex_trylock(tsdn, &decay->mtx)) {
		/* No need to wait if another thread is in progress. */
		return true;
	}

	bool epoch_advanced = arena_maybe_decay(tsdn, arena, decay, extents,
	    is_background_thread);
	UNUSED size_t npages_new;
	if (epoch_advanced) {
		/* Backlog is updated on epoch advance. */
		npages_new = decay->backlog[SMOOTHSTEP_NSTEPS-1];
	}
	malloc_mutex_unlock(tsdn, &decay->mtx);

	if (have_background_thread && background_thread_enabled() &&
	    epoch_advanced && !is_background_thread) {
		background_thread_interval_check(tsdn, arena, decay,
		    npages_new);
	}

	return false;
}
