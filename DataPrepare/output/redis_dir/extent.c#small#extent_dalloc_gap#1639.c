void
extent_dalloc_gap(tsdn_t *tsdn, arena_t *arena, extent_t *extent) {
	extent_hooks_t *extent_hooks = EXTENT_HOOKS_INITIALIZER;

	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	if (extent_register(tsdn, extent)) {
		extents_leak(tsdn, arena, &extent_hooks,
		    &arena->extents_retained, extent, false);
		return;
	}
	extent_dalloc_wrapper(tsdn, arena, &extent_hooks, extent);
}
