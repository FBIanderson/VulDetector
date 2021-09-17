void
prof_postfork_parent(tsdn_t *tsdn) {
	if (config_prof && opt_prof) {
		unsigned i;

		malloc_mutex_postfork_parent(tsdn,
		    &prof_thread_active_init_mtx);
		malloc_mutex_postfork_parent(tsdn, &next_thr_uid_mtx);
		malloc_mutex_postfork_parent(tsdn, &prof_gdump_mtx);
		malloc_mutex_postfork_parent(tsdn, &prof_dump_seq_mtx);
		malloc_mutex_postfork_parent(tsdn, &prof_active_mtx);
		for (i = 0; i < PROF_NCTX_LOCKS; i++) {
			malloc_mutex_postfork_parent(tsdn, &gctx_locks[i]);
		}
		for (i = 0; i < PROF_NTDATA_LOCKS; i++) {
			malloc_mutex_postfork_parent(tsdn, &tdata_locks[i]);
		}
		malloc_mutex_postfork_parent(tsdn, &tdatas_mtx);
		malloc_mutex_postfork_parent(tsdn, &bt2gctx_mtx);
		malloc_mutex_postfork_parent(tsdn, &prof_dump_mtx);
	}
}
