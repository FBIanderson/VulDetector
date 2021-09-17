static int
epoch_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	UNUSED uint64_t newval;

	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);
	WRITE(newval, uint64_t);
	if (newp != NULL) {
		ctl_refresh(tsd_tsdn(tsd));
	}
	READ(ctl_arenas->epoch, uint64_t);

	ret = 0;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);
	return ret;
}
