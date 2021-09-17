static int
arena_i_extent_hooks_ctl(tsd_t *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned arena_ind;
	arena_t *arena;

	malloc_mutex_lock(tsd_tsdn(tsd), &ctl_mtx);
	MIB_UNSIGNED(arena_ind, 1);
	if (arena_ind < narenas_total_get()) {
		extent_hooks_t *old_extent_hooks;
		arena = arena_get(tsd_tsdn(tsd), arena_ind, false);
		if (arena == NULL) {
			if (arena_ind >= narenas_auto) {
				ret = EFAULT;
				goto label_return;
			}
			old_extent_hooks =
			    (extent_hooks_t *)&extent_hooks_default;
			READ(old_extent_hooks, extent_hooks_t *);
			if (newp != NULL) {
				/* Initialize a new arena as a side effect. */
				extent_hooks_t *new_extent_hooks
				    JEMALLOC_CC_SILENCE_INIT(NULL);
				WRITE(new_extent_hooks, extent_hooks_t *);
				arena = arena_init(tsd_tsdn(tsd), arena_ind,
				    new_extent_hooks);
				if (arena == NULL) {
					ret = EFAULT;
					goto label_return;
				}
			}
		} else {
			if (newp != NULL) {
				extent_hooks_t *new_extent_hooks
				    JEMALLOC_CC_SILENCE_INIT(NULL);
				WRITE(new_extent_hooks, extent_hooks_t *);
				old_extent_hooks = extent_hooks_set(tsd, arena,
				    new_extent_hooks);
				READ(old_extent_hooks, extent_hooks_t *);
			} else {
				old_extent_hooks = extent_hooks_get(arena);
				READ(old_extent_hooks, extent_hooks_t *);
			}
		}
	} else {
		ret = EFAULT;
		goto label_return;
	}
	ret = 0;
label_return:
	malloc_mutex_unlock(tsd_tsdn(tsd), &ctl_mtx);
	return ret;
}
