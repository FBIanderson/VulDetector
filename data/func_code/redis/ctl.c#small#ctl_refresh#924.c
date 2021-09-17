static void
ctl_refresh(tsdn_t *tsdn) {
	unsigned i;
	ctl_arena_t *ctl_sarena = arenas_i(MALLCTL_ARENAS_ALL);
	VARIABLE_ARRAY(arena_t *, tarenas, ctl_arenas->narenas);

	/*
	 * Clear sum stats, since they will be merged into by
	 * ctl_arena_refresh().
	 */
	ctl_arena_clear(ctl_sarena);

	for (i = 0; i < ctl_arenas->narenas; i++) {
		tarenas[i] = arena_get(tsdn, i, false);
	}

	for (i = 0; i < ctl_arenas->narenas; i++) {
		ctl_arena_t *ctl_arena = arenas_i(i);
		bool initialized = (tarenas[i] != NULL);

		ctl_arena->initialized = initialized;
		if (initialized) {
			ctl_arena_refresh(tsdn, tarenas[i], ctl_sarena, i,
			    false);
		}
	}

	if (config_stats) {
		ctl_stats->allocated = ctl_sarena->astats->allocated_small +
		    atomic_load_zu(&ctl_sarena->astats->astats.allocated_large,
			ATOMIC_RELAXED);
		ctl_stats->active = (ctl_sarena->pactive << LG_PAGE);
		ctl_stats->metadata = atomic_load_zu(
		    &ctl_sarena->astats->astats.base, ATOMIC_RELAXED) +
		    atomic_load_zu(&ctl_sarena->astats->astats.internal,
			ATOMIC_RELAXED);
		ctl_stats->metadata_thp = atomic_load_zu(
		    &ctl_sarena->astats->astats.metadata_thp, ATOMIC_RELAXED);
		ctl_stats->resident = atomic_load_zu(
		    &ctl_sarena->astats->astats.resident, ATOMIC_RELAXED);
		ctl_stats->mapped = atomic_load_zu(
		    &ctl_sarena->astats->astats.mapped, ATOMIC_RELAXED);
		ctl_stats->retained = atomic_load_zu(
		    &ctl_sarena->astats->astats.retained, ATOMIC_RELAXED);

		ctl_background_thread_stats_read(tsdn);

#define READ_GLOBAL_MUTEX_PROF_DATA(i, mtx)				\
    malloc_mutex_lock(tsdn, &mtx);					\
    malloc_mutex_prof_read(tsdn, &ctl_stats->mutex_prof_data[i], &mtx);	\
    malloc_mutex_unlock(tsdn, &mtx);

		if (config_prof && opt_prof) {
			READ_GLOBAL_MUTEX_PROF_DATA(global_prof_mutex_prof,
			    bt2gctx_mtx);
		}
		if (have_background_thread) {
			READ_GLOBAL_MUTEX_PROF_DATA(
			    global_prof_mutex_background_thread,
			    background_thread_lock);
		} else {
			memset(&ctl_stats->mutex_prof_data[
			    global_prof_mutex_background_thread], 0,
			    sizeof(mutex_prof_data_t));
		}
		/* We own ctl mutex already. */
		malloc_mutex_prof_read(tsdn,
		    &ctl_stats->mutex_prof_data[global_prof_mutex_ctl],
		    &ctl_mtx);
#undef READ_GLOBAL_MUTEX_PROF_DATA
	}
	ctl_arenas->epoch++;
}
