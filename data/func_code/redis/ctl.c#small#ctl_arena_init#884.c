static unsigned
ctl_arena_init(tsd_t *tsd, extent_hooks_t *extent_hooks) {
	unsigned arena_ind;
	ctl_arena_t *ctl_arena;

	if ((ctl_arena = ql_last(&ctl_arenas->destroyed, destroyed_link)) !=
	    NULL) {
		ql_remove(&ctl_arenas->destroyed, ctl_arena, destroyed_link);
		arena_ind = ctl_arena->arena_ind;
	} else {
		arena_ind = ctl_arenas->narenas;
	}

	/* Trigger stats allocation. */
	if (arenas_i_impl(tsd, arena_ind, false, true) == NULL) {
		return UINT_MAX;
	}

	/* Initialize new arena. */
	if (arena_init(tsd_tsdn(tsd), arena_ind, extent_hooks) == NULL) {
		return UINT_MAX;
	}

	if (arena_ind == ctl_arenas->narenas) {
		ctl_arenas->narenas++;
	}

	return arena_ind;
}
