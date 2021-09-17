static int
max_background_threads_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	size_t oldval;

	if (!have_background_thread) {
		return ENOENT;
	}
	background_thread_ctl_init(tsd_tsdn(tsd));

	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);
	malloc_mutex_lock(tsd_tsdn(tsd), &background_thread_lock);
	if (newp == NULL) {
		oldval = max_background_threads;
		READ(oldval, size_t);
	} else {
		if (newlen != sizeof(size_t)) {
			ret = EINVAL;
			goto label_return;
		}
		oldval = max_background_threads;
		READ(oldval, size_t);

		size_t newval = *(size_t *)newp;
		if (newval == oldval) {
			ret = 0;
			goto label_return;
		}
		if (newval > opt_max_background_threads) {
			ret = EINVAL;
			goto label_return;
		}

		if (background_thread_enabled()) {
			if (!can_enable_background_thread) {
				malloc_printf("<jemalloc>: Error in dlsym("
			            "RTLD_NEXT, \"pthread_create\"). Cannot "
				    "enable background_thread\n");
				ret = EFAULT;
				goto label_return;
			}
			background_thread_enabled_set(tsd_tsdn(tsd), false);
			if (background_threads_disable(tsd)) {
				ret = EFAULT;
				goto label_return;
			}
			max_background_threads = newval;
			background_thread_enabled_set(tsd_tsdn(tsd), true);
			if (background_threads_enable(tsd)) {
				ret = EFAULT;
				goto label_return;
			}
		} else {
			max_background_threads = newval;
		}
	}
	ret = 0;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &background_thread_lock);
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);

	return ret;
}
