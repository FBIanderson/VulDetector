static bool
extent_dalloc_wrapper_try(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent) {
	bool err;

	assert(extent_base_get(extent) != NULL);
	assert(extent_size_get(extent) != 0);
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	extent_addr_set(extent, extent_base_get(extent));

	extent_hooks_assure_initialized(arena, r_extent_hooks);
	/* Try to deallocate. */
	if (*r_extent_hooks == &extent_hooks_default) {
		/* Call directly to propagate tsdn. */
		err = extent_dalloc_default_impl(extent_base_get(extent),
		    extent_size_get(extent));
	} else {
		extent_hook_pre_reentrancy(tsdn, arena);
		err = ((*r_extent_hooks)->dalloc == NULL ||
		    (*r_extent_hooks)->dalloc(*r_extent_hooks,
		    extent_base_get(extent), extent_size_get(extent),
		    extent_committed_get(extent), arena_ind_get(arena)));
		extent_hook_post_reentrancy(tsdn);
	}

	if (!err) {
		extent_dalloc(tsdn, arena, extent);
	}

	return err;
}
