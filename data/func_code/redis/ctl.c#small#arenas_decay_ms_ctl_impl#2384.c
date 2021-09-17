static int
arenas_decay_ms_ctl_impl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen, bool dirty) {
	int ret;

	if (oldp != NULL && oldlenp != NULL) {
		size_t oldval = (dirty ? arena_dirty_decay_ms_default_get() :
		    arena_muzzy_decay_ms_default_get());
		READ(oldval, ssize_t);
	}
	if (newp != NULL) {
		if (newlen != sizeof(ssize_t)) {
			ret = EINVAL;
			goto label_return;
		}
		if (dirty ? arena_dirty_decay_ms_default_set(*(ssize_t *)newp)
		    : arena_muzzy_decay_ms_default_set(*(ssize_t *)newp)) {
			ret = EFAULT;
			goto label_return;
		}
	}

	ret = 0;
label_return:
	return ret;
}
