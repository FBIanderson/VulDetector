static int
arenas_create_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	extent_hooks_t *extent_hooks;
	unsigned arena_ind;

	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);

	extent_hooks = (extent_hooks_t *)&extent_hooks_default;
	WRITE(extent_hooks, extent_hooks_t *);
	if ((arena_ind = ctl_arena_init(tsd, extent_hooks)) == UINT_MAX) {
		ret = EAGAIN;
		goto label_return;
	}
	READ(arena_ind, unsigned);

	ret = 0;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);
	return ret;
}
