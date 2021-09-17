static int
stats_mutexes_reset_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	if (!config_stats) {
		return ENOENT;
	}

	tsdn_t *tsdn = tsd_tsdn(tsd);

#define MUTEX_PROF_RESET(mtx)						\
    malloc_mutex_lock(tsdn, &mtx);					\
    malloc_mutex_prof_data_reset(tsdn, &mtx);				\
    malloc_mutex_unlock(tsdn, &mtx);

	/* Global mutexes: ctl and prof. */
	MUTEX_PROF_RESET(ctl_mtx);
	if (have_background_thread) {
		MUTEX_PROF_RESET(background_thread_lock);
	}
	if (config_prof && opt_prof) {
		MUTEX_PROF_RESET(bt2gctx_mtx);
	}


	/* Per arena mutexes. */
	unsigned n = narenas_total_get();

	for (unsigned i = 0; i < n; i++) {
		arena_t *arena = arena_get(tsdn, i, false);
		if (!arena) {
			continue;
		}
		MUTEX_PROF_RESET(arena->large_mtx);
		MUTEX_PROF_RESET(arena->extent_avail_mtx);
		MUTEX_PROF_RESET(arena->extents_dirty.mtx);
		MUTEX_PROF_RESET(arena->extents_muzzy.mtx);
		MUTEX_PROF_RESET(arena->extents_retained.mtx);
		MUTEX_PROF_RESET(arena->decay_dirty.mtx);
		MUTEX_PROF_RESET(arena->decay_muzzy.mtx);
		MUTEX_PROF_RESET(arena->tcache_ql_mtx);
		MUTEX_PROF_RESET(arena->base->mtx);

		for (szind_t i = 0; i < NBINS; i++) {
			bin_t *bin = &arena->bins[i];
			MUTEX_PROF_RESET(bin->lock);
		}
	}
#undef MUTEX_PROF_RESET
	return 0;
}
