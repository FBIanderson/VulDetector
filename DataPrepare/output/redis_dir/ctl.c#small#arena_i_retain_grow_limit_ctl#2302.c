static int
arena_i_retain_grow_limit_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned arena_ind;
	arena_t *arena;

	if (!opt_retain) {
		/* Only relevant when retain is enabled. */
		return ENOENT;
	}

	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);
	MIB_UNSIGNED(arena_ind, 1);
	if (arena_ind < narenas_total_get() && (arena =
	    arena_get(tsd_tsdn(tsd), arena_ind, false)) != NULL) {
		size_t old_limit, new_limit;
		if (newp != NULL) {
			WRITE(new_limit, size_t);
		}
		bool err = arena_retain_grow_limit_get_set(tsd, arena,
		    &old_limit, newp != NULL ? &new_limit : NULL);
		if (!err) {
			READ(old_limit, size_t);
			ret = 0;
		} else {
			ret = EFAULT;
		}
	} else {
		ret = EFAULT;
	}
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);
	return ret;
}
