void
malloc_mutex_lock_slow(malloc_mutex_t *mutex) {
	mutex_prof_data_t *data = &mutex->prof_data;
	UNUSED nstime_t before = NSTIME_ZERO_INITIALIZER;

	if (ncpus == 1) {
		goto label_spin_done;
	}

	int cnt = 0, max_cnt = MALLOC_MUTEX_MAX_SPIN;
	do {
		spin_cpu_spinwait();
		if (!malloc_mutex_trylock_final(mutex)) {
			data->n_spin_acquired++;
			return;
		}
	} while (cnt++ < max_cnt);

	if (!config_stats) {
		/* Only spin is useful when stats is off. */
		malloc_mutex_lock_final(mutex);
		return;
	}
label_spin_done:
	nstime_update(&before);
	/* Copy before to after to avoid clock skews. */
	nstime_t after;
	nstime_copy(&after, &before);
	uint32_t n_thds = atomic_fetch_add_u32(&data->n_waiting_thds, 1,
	    ATOMIC_RELAXED) + 1;
	/* One last try as above two calls may take quite some cycles. */
	if (!malloc_mutex_trylock_final(mutex)) {
		atomic_fetch_sub_u32(&data->n_waiting_thds, 1, ATOMIC_RELAXED);
		data->n_spin_acquired++;
		return;
	}

	/* True slow path. */
	malloc_mutex_lock_final(mutex);
	/* Update more slow-path only counters. */
	atomic_fetch_sub_u32(&data->n_waiting_thds, 1, ATOMIC_RELAXED);
	nstime_update(&after);

	nstime_t delta;
	nstime_copy(&delta, &after);
	nstime_subtract(&delta, &before);

	data->n_wait_times++;
	nstime_add(&data->tot_wait_time, &delta);
	if (nstime_compare(&data->max_wait_time, &delta) < 0) {
		nstime_copy(&data->max_wait_time, &delta);
	}
	if (n_thds > data->max_n_thds) {
		data->max_n_thds = n_thds;
	}
}
