ssize_t
arena_muzzy_decay_ms_default_get(void) {
	return atomic_load_zd(&muzzy_decay_ms_default, ATOMIC_RELAXED);
}
