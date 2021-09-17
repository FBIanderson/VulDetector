bool
prof_active_get(tsdn_t *tsdn) {
	bool prof_active_current;

	malloc_mutex_lock(tsdn, &prof_active_mtx);
	prof_active_current = prof_active;
	malloc_mutex_unlock(tsdn, &prof_active_mtx);
	return prof_active_current;
}
