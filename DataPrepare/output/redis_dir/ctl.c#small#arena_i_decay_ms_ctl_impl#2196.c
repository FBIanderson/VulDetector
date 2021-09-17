static int
arena_i_decay_ms_ctl_impl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen, bool dirty) {
	int ret;
	unsigned arena_ind;
	arena_t *arena;

	MIB_UNSIGNED(arena_ind, 1);
	arena = arena_get(tsd_tsdn(tsd), arena_ind, false);
	if (arena == NULL) {
		ret = EFAULT;
		goto label_return;
	}

	if (oldp != NULL && oldlenp != NULL) {
		size_t oldval = dirty ? arena_dirty_decay_ms_get(arena) :
		    arena_muzzy_decay_ms_get(arena);
		READ(oldval, ssize_t);
	}
	if (newp != NULL) {
		if (newlen != sizeof(ssize_t)) {
			ret = EINVAL;
			goto label_return;
		}
		if (dirty ? arena_dirty_decay_ms_set(tsd_tsdn(tsd), arena,
		    *(ssize_t *)newp) : arena_muzzy_decay_ms_set(tsd_tsdn(tsd),
		    arena, *(ssize_t *)newp)) {
			ret = EFAULT;
			goto label_return;
		}
	}

	ret = 0;
label_return:
	return ret;
}
