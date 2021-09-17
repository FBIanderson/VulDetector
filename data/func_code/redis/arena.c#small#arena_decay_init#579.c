static bool
arena_decay_init(arena_decay_t *decay, ssize_t decay_ms,
    arena_stats_decay_t *stats) {
	if (config_debug) {
		for (size_t i = 0; i < sizeof(arena_decay_t); i++) {
			assert(((char *)decay)[i] == 0);
		}
		decay->ceil_npages = 0;
	}
	if (malloc_mutex_init(&decay->mtx, "decay", WITNESS_RANK_DECAY,
	    malloc_mutex_rank_exclusive)) {
		return true;
	}
	decay->purging = false;
	arena_decay_reinit(decay, decay_ms);
	/* Memory is zeroed, so there is no need to clear stats. */
	if (config_stats) {
		decay->stats = stats;
	}
	return false;
}
