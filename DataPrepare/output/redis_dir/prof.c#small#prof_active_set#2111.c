bool
prof_active_set(tsdn_t *tsdn, bool active) {
	bool prof_active_old;

	malloc_mutex_lock(tsdn, &prof_active_mtx);
	prof_active_old = prof_active;
	prof_active = active;
	malloc_mutex_unlock(tsdn, &prof_active_mtx);
	return prof_active_old;
}
