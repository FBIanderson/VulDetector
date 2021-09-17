static int
background_thread_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	bool oldval;

	if (!have_background_thread) {
		return ENOENT;
	}
	background_thread_ctl_init(tsd_tsdn(tsd));

	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);
	malloc_mutex_lock(tsd_tsdn(tsd), &background_thread_lock);
	if (newp == NULL) {
		oldval = background_thread_enabled();
		READ(oldval, bool);
	} else {
		if (newlen != sizeof(bool)) {
			ret = EINVAL;
			goto label_return;
		}
		oldval = background_thread_enabled();
		READ(oldval, bool);

		bool newval = *(bool *)newp;
		if (newval == oldval) {
			ret = 0;
			goto label_return;
		}

		background_thread_enabled_set(tsd_tsdn(tsd), newval);
		if (newval) {
			if (!can_enable_background_thread) {
				malloc_printf("<jemalloc>: Error in dlsym("
			            "RTLD_NEXT, \"pthread_create\"). Cannot "
				    "enable background_thread\n");
				ret = EFAULT;
				goto label_return;
			}
			if (background_threads_enable(tsd)) {
				ret = EFAULT;
				goto label_return;
			}
		} else {
			if (background_threads_disable(tsd)) {
				ret = EFAULT;
				goto label_return;
			}
		}
	}
	ret = 0;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &background_thread_lock);
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);

	return ret;
}
