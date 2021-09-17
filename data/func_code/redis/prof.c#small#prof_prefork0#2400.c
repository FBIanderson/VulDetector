void
prof_prefork0(tsdn_t *tsdn) {
	if (config_prof && opt_prof) {
		unsigned i;

		malloc_mutex_prefork(tsdn, &prof_dump_mtx);
		malloc_mutex_prefork(tsdn, &bt2gctx_mtx);
		malloc_mutex_prefork(tsdn, &tdatas_mtx);
		for (i = 0; i < PROF_NTDATA_LOCKS; i++) {
			malloc_mutex_prefork(tsdn, &tdata_locks[i]);
		}
		for (i = 0; i < PROF_NCTX_LOCKS; i++) {
			malloc_mutex_prefork(tsdn, &gctx_locks[i]);
		}
	}
}
