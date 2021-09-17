static void
large_dalloc_prep_impl(tsdn_t *tsdn, arena_t *arena, extent_t *extent,
    bool junked_locked) {
	if (!junked_locked) {
		/* See comments in arena_bin_slabs_full_insert(). */
		if (!arena_is_auto(arena)) {
			malloc_mutex_lock(tsdn, &arena->large_mtx);
			extent_list_remove(&arena->large, extent);
			malloc_mutex_unlock(tsdn, &arena->large_mtx);
		}
		large_dalloc_maybe_junk(extent_addr_get(extent),
		    extent_usize_get(extent));
	} else {
		malloc_mutex_assert_owner(tsdn, &arena->large_mtx);
		if (!arena_is_auto(arena)) {
			extent_list_remove(&arena->large, extent);
		}
	}
	arena_extent_dalloc_large_prep(tsdn, arena, extent);
}
