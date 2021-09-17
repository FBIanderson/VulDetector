static void
stats_print_helper(emitter_t *emitter, bool merged, bool destroyed,
    bool unmerged, bool bins, bool large, bool mutex) {
	/*
	 * These should be deleted.  We keep them around for a while, to aid in
	 * the transition to the emitter code.
	 */
	size_t allocated, active, metadata, metadata_thp, resident, mapped,
	    retained;
	size_t num_background_threads;
	uint64_t background_thread_num_runs, background_thread_run_interval;

	CTL_GET("stats.allocated", &allocated, size_t);
	CTL_GET("stats.active", &active, size_t);
	CTL_GET("stats.metadata", &metadata, size_t);
	CTL_GET("stats.metadata_thp", &metadata_thp, size_t);
	CTL_GET("stats.resident", &resident, size_t);
	CTL_GET("stats.mapped", &mapped, size_t);
	CTL_GET("stats.retained", &retained, size_t);

	if (have_background_thread) {
		CTL_GET("stats.background_thread.num_threads",
		    &num_background_threads, size_t);
		CTL_GET("stats.background_thread.num_runs",
		    &background_thread_num_runs, uint64_t);
		CTL_GET("stats.background_thread.run_interval",
		    &background_thread_run_interval, uint64_t);
	} else {
		num_background_threads = 0;
		background_thread_num_runs = 0;
		background_thread_run_interval = 0;
	}

	/* Generic global stats. */
	emitter_json_dict_begin(emitter, "stats");
	emitter_json_kv(emitter, "allocated", emitter_type_size, &allocated);
	emitter_json_kv(emitter, "active", emitter_type_size, &active);
	emitter_json_kv(emitter, "metadata", emitter_type_size, &metadata);
	emitter_json_kv(emitter, "metadata_thp", emitter_type_size,
	    &metadata_thp);
	emitter_json_kv(emitter, "resident", emitter_type_size, &resident);
	emitter_json_kv(emitter, "mapped", emitter_type_size, &mapped);
	emitter_json_kv(emitter, "retained", emitter_type_size, &retained);

	emitter_table_printf(emitter, "Allocated: %zu, active: %zu, "
	    "metadata: %zu (n_thp %zu), resident: %zu, mapped: %zu, "
	    "retained: %zu\n", allocated, active, metadata, metadata_thp,
	    resident, mapped, retained);

	/* Background thread stats. */
	emitter_json_dict_begin(emitter, "background_thread");
	emitter_json_kv(emitter, "num_threads", emitter_type_size,
	    &num_background_threads);
	emitter_json_kv(emitter, "num_runs", emitter_type_uint64,
	    &background_thread_num_runs);
	emitter_json_kv(emitter, "run_interval", emitter_type_uint64,
	    &background_thread_run_interval);
	emitter_json_dict_end(emitter); /* Close "background_thread". */

	emitter_table_printf(emitter, "Background threads: %zu, "
	    "num_runs: %"FMTu64", run_interval: %"FMTu64" ns\n",
	    num_background_threads, background_thread_num_runs,
	    background_thread_run_interval);

	if (mutex) {
		emitter_row_t row;
		emitter_col_t name;
		emitter_col_t col64[mutex_prof_num_uint64_t_counters];
		emitter_col_t col32[mutex_prof_num_uint32_t_counters];

		emitter_row_init(&row);
		mutex_stats_init_cols(&row, "", &name, col64, col32);

		emitter_table_row(emitter, &row);
		emitter_json_dict_begin(emitter, "mutexes");

		for (int i = 0; i < mutex_prof_num_global_mutexes; i++) {
			mutex_stats_read_global(global_mutex_names[i], &name,
			    col64, col32);
			emitter_json_dict_begin(emitter, global_mutex_names[i]);
			mutex_stats_emit(emitter, &row, col64, col32);
			emitter_json_dict_end(emitter);
		}

		emitter_json_dict_end(emitter); /* Close "mutexes". */
	}

	emitter_json_dict_end(emitter); /* Close "stats". */

	if (merged || destroyed || unmerged) {
		unsigned narenas;

		emitter_json_dict_begin(emitter, "stats.arenas");

		CTL_GET("arenas.narenas", &narenas, unsigned);
		size_t mib[3];
		size_t miblen = sizeof(mib) / sizeof(size_t);
		size_t sz;
		VARIABLE_ARRAY(bool, initialized, narenas);
		bool destroyed_initialized;
		unsigned i, j, ninitialized;

		xmallctlnametomib("arena.0.initialized", mib, &miblen);
		for (i = ninitialized = 0; i < narenas; i++) {
			mib[1] = i;
			sz = sizeof(bool);
			xmallctlbymib(mib, miblen, &initialized[i], &sz,
			    NULL, 0);
			if (initialized[i]) {
				ninitialized++;
			}
		}
		mib[1] = MALLCTL_ARENAS_DESTROYED;
		sz = sizeof(bool);
		xmallctlbymib(mib, miblen, &destroyed_initialized, &sz,
		    NULL, 0);

		/* Merged stats. */
		if (merged && (ninitialized > 1 || !unmerged)) {
			/* Print merged arena stats. */
			emitter_table_printf(emitter, "Merged arenas stats:\n");
			emitter_json_dict_begin(emitter, "merged");
			stats_arena_print(emitter, MALLCTL_ARENAS_ALL, bins,
			    large, mutex);
			emitter_json_dict_end(emitter); /* Close "merged". */
		}

		/* Destroyed stats. */
		if (destroyed_initialized && destroyed) {
			/* Print destroyed arena stats. */
			emitter_table_printf(emitter,
			    "Destroyed arenas stats:\n");
			emitter_json_dict_begin(emitter, "destroyed");
			stats_arena_print(emitter, MALLCTL_ARENAS_DESTROYED,
			    bins, large, mutex);
			emitter_json_dict_end(emitter); /* Close "destroyed". */
		}

		/* Unmerged stats. */
		if (unmerged) {
			for (i = j = 0; i < narenas; i++) {
				if (initialized[i]) {
					char arena_ind_str[20];
					malloc_snprintf(arena_ind_str,
					    sizeof(arena_ind_str), "%u", i);
					emitter_json_dict_begin(emitter,
					    arena_ind_str);
					emitter_table_printf(emitter,
					    "arenas[%s]:\n", arena_ind_str);
					stats_arena_print(emitter, i, bins,
					    large, mutex);
					/* Close "<arena-ind>". */
					emitter_json_dict_end(emitter);
				}
			}
		}
		emitter_json_dict_end(emitter); /* Close "stats.arenas". */
	}
}
