static int
thread_arena_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	arena_t *oldarena;
	unsigned newind, oldind;

	oldarena = arena_choose(tsd, NULL);
	if (oldarena == NULL) {
		return EAGAIN;
	}
	newind = oldind = arena_ind_get(oldarena);
	WRITE(newind, unsigned);
	READ(oldind, unsigned);

	if (newind != oldind) {
		arena_t *newarena;

		if (newind >= narenas_total_get()) {
			/* New arena index is out of range. */
			ret = EFAULT;
			goto label_return;
		}

		if (have_percpu_arena &&
		    PERCPU_ARENA_ENABLED(opt_percpu_arena)) {
			if (newind < percpu_arena_ind_limit(opt_percpu_arena)) {
				/*
				 * If perCPU arena is enabled, thread_arena
				 * control is not allowed for the auto arena
				 * range.
				 */
				ret = EPERM;
				goto label_return;
			}
		}

		/* Initialize arena if necessary. */
		newarena = arena_get(tsd_tsdn(tsd), newind, true);
		if (newarena == NULL) {
			ret = EAGAIN;
			goto label_return;
		}
		/* Set new arena/tcache associations. */
		arena_migrate(tsd, oldind, newind);
		if (tcache_available(tsd)) {
			tcache_arena_reassociate(tsd_tsdn(tsd),
			    tsd_tcachep_get(tsd), newarena);
		}
	}

	ret = 0;
label_return:
	return ret;
}
