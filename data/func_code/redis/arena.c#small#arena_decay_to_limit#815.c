static void
arena_decay_to_limit(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    extents_t *extents, bool all, size_t npages_limit, size_t npages_decay_max,
    bool is_background_thread) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 1);
	malloc_mutex_assert_owner(tsdn, &decay->mtx);

	if (decay->purging) {
		return;
	}
	decay->purging = true;
	malloc_mutex_unlock(tsdn, &decay->mtx);

	extent_hooks_t *extent_hooks = extent_hooks_get(arena);

	extent_list_t decay_extents;
	extent_list_init(&decay_extents);

	size_t npurge = arena_stash_decayed(tsdn, arena, &extent_hooks, extents,
	    npages_limit, npages_decay_max, &decay_extents);
	if (npurge != 0) {
		UNUSED size_t npurged = arena_decay_stashed(tsdn, arena,
		    &extent_hooks, decay, extents, all, &decay_extents,
		    is_background_thread);
		assert(npurged == npurge);
	}

	malloc_mutex_lock(tsdn, &decay->mtx);
	decay->purging = false;
}
