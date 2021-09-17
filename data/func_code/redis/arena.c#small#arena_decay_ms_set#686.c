static bool
arena_decay_ms_set(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    extents_t *extents, ssize_t decay_ms) {
	if (!arena_decay_ms_valid(decay_ms)) {
		return true;
	}

	malloc_mutex_lock(tsdn, &decay->mtx);
	/*
	 * Restart decay backlog from scratch, which may cause many dirty pages
	 * to be immediately purged.  It would conceptually be possible to map
	 * the old backlog onto the new backlog, but there is no justification
	 * for such complexity since decay_ms changes are intended to be
	 * infrequent, either between the {-1, 0, >0} states, or a one-time
	 * arbitrary change during initial arena configuration.
	 */
	arena_decay_reinit(decay, decay_ms);
	arena_maybe_decay(tsdn, arena, decay, extents, false);
	malloc_mutex_unlock(tsdn, &decay->mtx);

	return false;
}
