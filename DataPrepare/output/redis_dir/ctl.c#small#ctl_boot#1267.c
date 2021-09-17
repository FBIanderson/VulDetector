bool
ctl_boot(void) {
	if (malloc_mutex_init(&ctl_mtx, "ctl", WITNESS_RANK_CTL,
	    malloc_mutex_rank_exclusive)) {
		return true;
	}

	ctl_initialized = false;

	return false;
}
