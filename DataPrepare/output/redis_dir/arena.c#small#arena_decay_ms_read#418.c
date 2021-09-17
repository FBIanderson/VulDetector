static ssize_t
arena_decay_ms_read(arena_decay_t *decay) {
	return atomic_load_zd(&decay->time_ms, ATOMIC_RELAXED);
}
