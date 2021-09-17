static bool
arena_decay_ms_valid(ssize_t decay_ms) {
	if (decay_ms < -1) {
		return false;
	}
	if (decay_ms == -1 || (uint64_t)decay_ms <= NSTIME_SEC_MAX *
	    KQU(1000)) {
		return true;
	}
	return false;
}
