static int
arena_i_destroy_ctl(tsd_t *tsd, const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen) {
	int ret;
	unsigned arena_ind;
	arena_t *arena;
	ctl_arena_t *ctl_darena, *ctl_arena;

	ret = arena_i_reset_destroy_helper(tsd, mib, miblen, oldp, oldlenp,
	    newp, newlen, &arena_ind, &arena);
	if (ret != 0) {
		goto label_return;
	}

	if (arena_nthreads_get(arena, false) != 0 || arena_nthreads_get(arena,
	    true) != 0) {
		ret = EFAULT;
		goto label_return;
	}

	arena_reset_prepare_background_thread(tsd, arena_ind);
	/* Merge stats after resetting and purging arena. */
	arena_reset(tsd, arena);
	arena_decay(tsd_tsdn(tsd), arena, false, true);
	ctl_darena = arenas_i(MALLCTL_ARENAS_DESTROYED);
	ctl_darena->initialized = true;
	ctl_arena_refresh(tsd_tsdn(tsd), arena, ctl_darena, arena_ind, true);
	/* Destroy arena. */
	arena_destroy(tsd, arena);
	ctl_arena = arenas_i(arena_ind);
	ctl_arena->initialized = false;
	/* Record arena index for later recycling via arenas.create. */
	ql_elm_new(ctl_arena, destroyed_link);
	ql_tail_insert(&ctl_arenas->destroyed, ctl_arena, destroyed_link);
	arena_reset_finish_background_thread(tsd, arena_ind);

	assert(ret == 0);
label_return:
	return ret;
}
