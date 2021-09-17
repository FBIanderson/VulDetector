void
extent_dalloc_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent) {
	assert(extent_dumpable_get(extent));
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	/*
	 * Deregister first to avoid a race with other allocating threads, and
	 * reregister if deallocation fails.
	 */
	extent_deregister(tsdn, extent);
	if (!extent_dalloc_wrapper_try(tsdn, arena, r_extent_hooks, extent)) {
		return;
	}

	extent_reregister(tsdn, extent);
	if (*r_extent_hooks != &extent_hooks_default) {
		extent_hook_pre_reentrancy(tsdn, arena);
	}
	/* Try to decommit; purge if that fails. */
	bool zeroed;
	if (!extent_committed_get(extent)) {
		zeroed = true;
	} else if (!extent_decommit_wrapper(tsdn, arena, r_extent_hooks, extent,
	    0, extent_size_get(extent))) {
		zeroed = true;
	} else if ((*r_extent_hooks)->purge_forced != NULL &&
	    !(*r_extent_hooks)->purge_forced(*r_extent_hooks,
	    extent_base_get(extent), extent_size_get(extent), 0,
	    extent_size_get(extent), arena_ind_get(arena))) {
		zeroed = true;
	} else if (extent_state_get(extent) == extent_state_muzzy ||
	    ((*r_extent_hooks)->purge_lazy != NULL &&
	    !(*r_extent_hooks)->purge_lazy(*r_extent_hooks,
	    extent_base_get(extent), extent_size_get(extent), 0,
	    extent_size_get(extent), arena_ind_get(arena)))) {
		zeroed = false;
	} else {
		zeroed = false;
	}
	if (*r_extent_hooks != &extent_hooks_default) {
		extent_hook_post_reentrancy(tsdn);
	}
	extent_zeroed_set(extent, zeroed);

	if (config_prof) {
		extent_gdump_sub(tsdn, extent);
	}

	extent_record(tsdn, arena, r_extent_hooks, &arena->extents_retained,
	    extent, false);
}
