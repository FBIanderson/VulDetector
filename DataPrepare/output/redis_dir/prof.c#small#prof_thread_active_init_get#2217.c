bool
prof_thread_active_init_get(tsdn_t *tsdn) {
	bool active_init;

	malloc_mutex_lock(tsdn, &prof_thread_active_init_mtx);
	active_init = prof_thread_active_init;
	malloc_mutex_unlock(tsdn, &prof_thread_active_init_mtx);
	return active_init;
}
