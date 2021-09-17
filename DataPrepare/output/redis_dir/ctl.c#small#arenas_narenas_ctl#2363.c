static int
arenas_narenas_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned narenas;

	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);
	READONLY();
	if (*oldlenp != sizeof(unsigned)) {
		ret = EINVAL;
		goto label_return;
	}
	narenas = ctl_arenas->narenas;
	READ(narenas, unsigned);

	ret = 0;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);
	return ret;
}
