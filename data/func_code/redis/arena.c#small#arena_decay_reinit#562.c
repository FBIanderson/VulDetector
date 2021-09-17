static void
arena_decay_reinit(arena_decay_t *decay, ssize_t decay_ms) {
	arena_decay_ms_write(decay, decay_ms);
	if (decay_ms > 0) {
		nstime_init(&decay->interval, (uint64_t)decay_ms *
		    KQU(1000000));
		nstime_idivide(&decay->interval, SMOOTHSTEP_NSTEPS);
	}

	nstime_init(&decay->epoch, 0);
	nstime_update(&decay->epoch);
	decay->jitter_state = (uint64_t)(uintptr_t)decay;
	arena_decay_deadline_init(decay);
	decay->nunpurged = 0;
	memset(decay->backlog, 0, SMOOTHSTEP_NSTEPS * sizeof(size_t));
}
