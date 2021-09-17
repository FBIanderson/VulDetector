void
prof_prefork1(tsdn_t *tsdn) {
	if (config_prof && opt_prof) {
		malloc_mutex_prefork(tsdn, &prof_active_mtx);
		malloc_mutex_prefork(tsdn, &prof_dump_seq_mtx);
		malloc_mutex_prefork(tsdn, &prof_gdump_mtx);
		malloc_mutex_prefork(tsdn, &next_thr_uid_mtx);
		malloc_mutex_prefork(tsdn, &prof_thread_active_init_mtx);
	}
}
