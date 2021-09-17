static int
arena_i_initialized_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	tsdn_t *tsdn = tsd_tsdn(tsd);
	unsigned arena_ind;
	bool initialized;

	READONLY();
	MIB_UNSIGNED(arena_ind, 1);

	malloc_mutex_lock(tsdn, &ctl_mtx);
	initialized = arenas_i(arena_ind)->initialized;
	malloc_mutex_unlock(tsdn, &ctl_mtx);

	READ(initialized, bool);

	ret = 0;
label_return:
	return ret;
}
