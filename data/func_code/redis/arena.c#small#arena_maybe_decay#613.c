static bool
arena_maybe_decay(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    extents_t *extents, bool is_background_thread) {
	malloc_mutex_assert_owner(tsdn, &decay->mtx);

	/* Purge all or nothing if the option is disabled. */
	ssize_t decay_ms = arena_decay_ms_read(decay);
	if (decay_ms <= 0) {
		if (decay_ms == 0) {
			arena_decay_to_limit(tsdn, arena, decay, extents, false,
			    0, extents_npages_get(extents),
			    is_background_thread);
		}
		return false;
	}

	nstime_t time;
	nstime_init(&time, 0);
	nstime_update(&time);
	if (unlikely(!nstime_monotonic() && nstime_compare(&decay->epoch, &time)
	    > 0)) {
		/*
		 * Time went backwards.  Move the epoch back in time and
		 * generate a new deadline, with the expectation that time
		 * typically flows forward for long enough periods of time that
		 * epochs complete.  Unfortunately, this strategy is susceptible
		 * to clock jitter triggering premature epoch advances, but
		 * clock jitter estimation and compensation isn't feasible here
		 * because calls into this code are event-driven.
		 */
		nstime_copy(&decay->epoch, &time);
		arena_decay_deadline_init(decay);
	} else {
		/* Verify that time does not go backwards. */
		assert(nstime_compare(&decay->epoch, &time) <= 0);
	}

	/*
	 * If the deadline has been reached, advance to the current epoch and
	 * purge to the new limit if necessary.  Note that dirty pages created
	 * during the current epoch are not subject to purge until a future
	 * epoch, so as a result purging only happens during epoch advances, or
	 * being triggered by background threads (scheduled event).
	 */
	bool advance_epoch = arena_decay_deadline_reached(decay, &time);
	if (advance_epoch) {
		arena_decay_epoch_advance(tsdn, arena, decay, extents, &time,
		    is_background_thread);
	} else if (is_background_thread) {
		arena_decay_try_purge(tsdn, arena, decay, extents,
		    extents_npages_get(extents),
		    arena_decay_backlog_npages_limit(decay),
		    is_background_thread);
	}

	return advance_epoch;
}
