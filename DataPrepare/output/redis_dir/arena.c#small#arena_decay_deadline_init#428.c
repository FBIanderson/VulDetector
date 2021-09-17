static void
arena_decay_deadline_init(arena_decay_t *decay) {
	/*
	 * Generate a new deadline that is uniformly random within the next
	 * epoch after the current one.
	 */
	nstime_copy(&decay->deadline, &decay->epoch);
	nstime_add(&decay->deadline, &decay->interval);
	if (arena_decay_ms_read(decay) > 0) {
		nstime_t jitter;

		nstime_init(&jitter, prng_range_u64(&decay->jitter_state,
		    nstime_ns(&decay->interval)));
		nstime_add(&decay->deadline, &jitter);
	}
}
