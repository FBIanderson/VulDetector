void
extent_destroy_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent) {
	assert(extent_base_get(extent) != NULL);
	assert(extent_size_get(extent) != 0);
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	/* Deregister first to avoid a race with other allocating threads. */
	extent_deregister(tsdn, extent);

	extent_addr_set(extent, extent_base_get(extent));

	extent_hooks_assure_initialized(arena, r_extent_hooks);
	/* Try to destroy; silently fail otherwise. */
	if (*r_extent_hooks == &extent_hooks_default) {
		/* Call directly to propagate tsdn. */
		extent_destroy_default_impl(extent_base_get(extent),
		    extent_size_get(extent));
	} else if ((*r_extent_hooks)->destroy != NULL) {
		extent_hook_pre_reentrancy(tsdn, arena);
		(*r_extent_hooks)->destroy(*r_extent_hooks,
		    extent_base_get(extent), extent_size_get(extent),
		    extent_committed_get(extent), arena_ind_get(arena));
		extent_hook_post_reentrancy(tsdn);
	}

	extent_dalloc(tsdn, arena, extent);
}
