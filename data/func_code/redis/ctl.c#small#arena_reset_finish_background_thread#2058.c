static void
arena_reset_finish_background_thread(tsd_t *tsd, unsigned arena_ind) {
	if (have_background_thread) {
		if (background_thread_enabled()) {
			unsigned ind = arena_ind % ncpus;
			background_thread_info_t *info =
			    &background_thread_info[ind];
			assert(info->state == background_thread_paused);
			malloc_mutex_lock(tsd_tsdn(tsd), &info->mtx);
			info->state = background_thread_started;
			malloc_mutex_unlock(tsd_tsdn(tsd), &info->mtx);
		}
		malloc_mutex_unlock(tsd_tsdn(tsd), &background_thread_lock);
	}
}
