bool
prof_boot2(tsd_t *tsd) {
	cassert(config_prof);

	if (opt_prof) {
		unsigned i;

		lg_prof_sample = opt_lg_prof_sample;

		prof_active = opt_prof_active;
		if (malloc_mutex_init(&prof_active_mtx, "prof_active",
		    WITNESS_RANK_PROF_ACTIVE, malloc_mutex_rank_exclusive)) {
			return true;
		}

		prof_gdump_val = opt_prof_gdump;
		if (malloc_mutex_init(&prof_gdump_mtx, "prof_gdump",
		    WITNESS_RANK_PROF_GDUMP, malloc_mutex_rank_exclusive)) {
			return true;
		}

		prof_thread_active_init = opt_prof_thread_active_init;
		if (malloc_mutex_init(&prof_thread_active_init_mtx,
		    "prof_thread_active_init",
		    WITNESS_RANK_PROF_THREAD_ACTIVE_INIT,
		    malloc_mutex_rank_exclusive)) {
			return true;
		}

		if (ckh_new(tsd, &bt2gctx, PROF_CKH_MINITEMS, prof_bt_hash,
		    prof_bt_keycomp)) {
			return true;
		}
		if (malloc_mutex_init(&bt2gctx_mtx, "prof_bt2gctx",
		    WITNESS_RANK_PROF_BT2GCTX, malloc_mutex_rank_exclusive)) {
			return true;
		}

		tdata_tree_new(&tdatas);
		if (malloc_mutex_init(&tdatas_mtx, "prof_tdatas",
		    WITNESS_RANK_PROF_TDATAS, malloc_mutex_rank_exclusive)) {
			return true;
		}

		next_thr_uid = 0;
		if (malloc_mutex_init(&next_thr_uid_mtx, "prof_next_thr_uid",
		    WITNESS_RANK_PROF_NEXT_THR_UID, malloc_mutex_rank_exclusive)) {
			return true;
		}

		if (malloc_mutex_init(&prof_dump_seq_mtx, "prof_dump_seq",
		    WITNESS_RANK_PROF_DUMP_SEQ, malloc_mutex_rank_exclusive)) {
			return true;
		}
		if (malloc_mutex_init(&prof_dump_mtx, "prof_dump",
		    WITNESS_RANK_PROF_DUMP, malloc_mutex_rank_exclusive)) {
			return true;
		}

		if (opt_prof_final && opt_prof_prefix[0] != '\0' &&
		    atexit(prof_fdump) != 0) {
			malloc_write("<jemalloc>: Error in atexit()\n");
			if (opt_abort) {
				abort();
			}
		}

		gctx_locks = (malloc_mutex_t *)base_alloc(tsd_tsdn(tsd),
		    b0get(), PROF_NCTX_LOCKS * sizeof(malloc_mutex_t),
		    CACHELINE);
		if (gctx_locks == NULL) {
			return true;
		}
		for (i = 0; i < PROF_NCTX_LOCKS; i++) {
			if (malloc_mutex_init(&gctx_locks[i], "prof_gctx",
			    WITNESS_RANK_PROF_GCTX,
			    malloc_mutex_rank_exclusive)) {
				return true;
			}
		}

		tdata_locks = (malloc_mutex_t *)base_alloc(tsd_tsdn(tsd),
		    b0get(), PROF_NTDATA_LOCKS * sizeof(malloc_mutex_t),
		    CACHELINE);
		if (tdata_locks == NULL) {
			return true;
		}
		for (i = 0; i < PROF_NTDATA_LOCKS; i++) {
			if (malloc_mutex_init(&tdata_locks[i], "prof_tdata",
			    WITNESS_RANK_PROF_TDATA,
			    malloc_mutex_rank_exclusive)) {
				return true;
			}
		}
	}

#ifdef JEMALLOC_PROF_LIBGCC
	/*
	 * Cause the backtracing machinery to allocate its internal state
	 * before enabling profiling.
	 */
	_Unwind_Backtrace(prof_unwind_init_callback, NULL);
#endif

	prof_booted = true;

	return false;
}
