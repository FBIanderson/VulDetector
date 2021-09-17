static bool
extent_coalesce(tsdn_t *tsdn, arena_t *arena, extent_hooks_t **r_extent_hooks,
    extents_t *extents, extent_t *inner, extent_t *outer, bool forward,
    bool growing_retained) {
	assert(extent_can_coalesce(arena, extents, inner, outer));

	extent_activate_locked(tsdn, arena, extents, outer);

	malloc_mutex_unlock(tsdn, &extents->mtx);
	bool err = extent_merge_impl(tsdn, arena, r_extent_hooks,
	    forward ? inner : outer, forward ? outer : inner, growing_retained);
	malloc_mutex_lock(tsdn, &extents->mtx);

	if (err) {
		extent_deactivate_locked(tsdn, arena, extents, outer);
	}

	return err;
}
