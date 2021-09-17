void
arena_extents_dirty_dalloc(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	extents_dalloc(tsdn, arena, r_extent_hooks, &arena->extents_dirty,
	    extent);
	if (arena_dirty_decay_ms_get(arena) == 0) {
		arena_decay_dirty(tsdn, arena, false, true);
	} else {
		arena_background_thread_inactivity_check(tsdn, arena, false);
	}
}
