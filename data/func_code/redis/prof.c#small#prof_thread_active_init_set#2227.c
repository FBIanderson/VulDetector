bool
prof_thread_active_init_set(tsdn_t *tsdn, bool active_init) {
	bool active_init_old;

	malloc_mutex_lock(tsdn, &prof_thread_active_init_mtx);
	active_init_old = prof_thread_active_init;
	prof_thread_active_init = active_init;
	malloc_mutex_unlock(tsdn, &prof_thread_active_init_mtx);
	return active_init_old;
}
