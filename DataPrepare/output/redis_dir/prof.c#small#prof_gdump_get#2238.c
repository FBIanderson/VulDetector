bool
prof_gdump_get(tsdn_t *tsdn) {
	bool prof_gdump_current;

	malloc_mutex_lock(tsdn, &prof_gdump_mtx);
	prof_gdump_current = prof_gdump_val;
	malloc_mutex_unlock(tsdn, &prof_gdump_mtx);
	return prof_gdump_current;
}
