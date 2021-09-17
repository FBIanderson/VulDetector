bool
arena_dirty_decay_ms_default_set(ssize_t decay_ms) {
	if (!arena_decay_ms_valid(decay_ms)) {
		return true;
	}
	atomic_store_zd(&dirty_decay_ms_default, decay_ms, ATOMIC_RELAXED);
	return false;
}
