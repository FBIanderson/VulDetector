ssize_t
arena_dirty_decay_ms_default_get(void) {
	return atomic_load_zd(&dirty_decay_ms_default, ATOMIC_RELAXED);
}
