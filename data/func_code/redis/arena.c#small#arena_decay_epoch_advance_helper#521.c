static void
arena_decay_epoch_advance_helper(arena_decay_t *decay, const nstime_t *time,
    size_t current_npages) {
	assert(arena_decay_deadline_reached(decay, time));

	nstime_t delta;
	nstime_copy(&delta, time);
	nstime_subtract(&delta, &decay->epoch);

	uint64_t nadvance_u64 = nstime_divide(&delta, &decay->interval);
	assert(nadvance_u64 > 0);

	/* Add nadvance_u64 decay intervals to epoch. */
	nstime_copy(&delta, &decay->interval);
	nstime_imultiply(&delta, nadvance_u64);
	nstime_add(&decay->epoch, &delta);

	/* Set a new deadline. */
	arena_decay_deadline_init(decay);

	/* Update the backlog. */
	arena_decay_backlog_update(decay, nadvance_u64, current_npages);
}
