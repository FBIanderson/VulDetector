static void
arena_reset_prepare_background_thread(tsd_t *tsd, unsigned arena_ind) {
	/* Temporarily disable the background thread during arena reset. */
	if (have_background_thread) {
		malloc_mutex_lock(tsd_tsdn(tsd), &background_thread_lock);
		if (background_thread_enabled()) {
			unsigned ind = arena_ind % ncpus;
			background_thread_info_t *info =
			    &background_thread_info[ind];
			assert(info->state == background_thread_started);
			malloc_mutex_lock(tsd_tsdn(tsd), &info->mtx);
			info->state = background_thread_paused;
			malloc_mutex_unlock(tsd_tsdn(tsd), &info->mtx);
		}
	}
}
