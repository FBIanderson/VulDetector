static void
arena_decay_ms_write(arena_decay_t *decay, ssize_t decay_ms) {
	atomic_store_zd(&decay->time_ms, decay_ms, ATOMIC_RELAXED);
}
