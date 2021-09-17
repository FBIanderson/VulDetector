static int
arena_i_dss_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	const char *dss = NULL;
	unsigned arena_ind;
	dss_prec_t dss_prec_old = dss_prec_limit;
	dss_prec_t dss_prec = dss_prec_limit;

	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);
	WRITE(dss, const char *);
	MIB_UNSIGNED(arena_ind, 1);
	if (dss != NULL) {
		int i;
		bool match = false;

		for (i = 0; i < dss_prec_limit; i++) {
			if (strcmp(dss_prec_names[i], dss) == 0) {
				dss_prec = i;
				match = true;
				break;
			}
		}

		if (!match) {
			ret = EINVAL;
			goto label_return;
		}
	}

	/*
	 * Access via index narenas is deprecated, and scheduled for removal in
	 * 6.0.0.
	 */
	if (arena_ind == MALLCTL_ARENAS_ALL || arena_ind ==
	    ctl_arenas->narenas) {
		if (dss_prec != dss_prec_limit &&
		    extent_dss_prec_set(dss_prec)) {
			ret = EFAULT;
			goto label_return;
		}
		dss_prec_old = extent_dss_prec_get();
	} else {
		arena_t *arena = arena_get(tsd_tsdn(tsd), arena_ind, false);
		if (arena == NULL || (dss_prec != dss_prec_limit &&
		    arena_dss_prec_set(arena, dss_prec))) {
			ret = EFAULT;
			goto label_return;
		}
		dss_prec_old = arena_dss_prec_get(arena);
	}

	dss = dss_prec_names[dss_prec_old];
	READ(dss, const char *);

	ret = 0;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);
	return ret;
}
