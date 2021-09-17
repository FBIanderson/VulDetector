bool
prof_gdump_set(tsdn_t *tsdn, bool gdump) {
	bool prof_gdump_old;

	malloc_mutex_lock(tsdn, &prof_gdump_mtx);
	prof_gdump_old = prof_gdump_val;
	prof_gdump_val = gdump;
	malloc_mutex_unlock(tsdn, &prof_gdump_mtx);
	return prof_gdump_old;
}
