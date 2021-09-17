static int
arenas_lookup_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned arena_ind;
	void *ptr;
	extent_t *extent;
	arena_t *arena;

	ptr = NULL;
	ret = EINVAL;
	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);
	WRITE(ptr, void *);
	extent = iealloc(tsd_tsdn(tsd), ptr);
	if (extent == NULL)
		goto label_return;

	arena = extent_arena_get(extent);
	if (arena == NULL)
		goto label_return;

	arena_ind = arena_ind_get(arena);
	READ(arena_ind, unsigned);

	ret = 0;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);
	return ret;
}
