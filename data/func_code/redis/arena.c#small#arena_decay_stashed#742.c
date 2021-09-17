static size_t
arena_decay_stashed(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, arena_decay_t *decay, extents_t *extents,
    bool all, extent_list_t *decay_extents, bool is_background_thread) {
	UNUSED size_t nmadvise, nunmapped;
	size_t npurged;

	if (config_stats) {
		nmadvise = 0;
		nunmapped = 0;
	}
	npurged = 0;

	ssize_t muzzy_decay_ms = arena_muzzy_decay_ms_get(arena);
	for (extent_t *extent = extent_list_first(decay_extents); extent !=
	    NULL; extent = extent_list_first(decay_extents)) {
		if (config_stats) {
			nmadvise++;
		}
		size_t npages = extent_size_get(extent) >> LG_PAGE;
		npurged += npages;
		extent_list_remove(decay_extents, extent);
		switch (extents_state_get(extents)) {
		case extent_state_active:
			not_reached();
		case extent_state_dirty:
			if (!all && muzzy_decay_ms != 0 &&
			    !extent_purge_lazy_wrapper(tsdn, arena,
			    r_extent_hooks, extent, 0,
			    extent_size_get(extent))) {
				extents_dalloc(tsdn, arena, r_extent_hooks,
				    &arena->extents_muzzy, extent);
				arena_background_thread_inactivity_check(tsdn,
				    arena, is_background_thread);
				break;
			}
			/* Fall through. */
		case extent_state_muzzy:
			extent_dalloc_wrapper(tsdn, arena, r_extent_hooks,
			    extent);
			if (config_stats) {
				nunmapped += npages;
			}
			break;
		case extent_state_retained:
		default:
			not_reached();
		}
	}

	if (config_stats) {
		arena_stats_lock(tsdn, &arena->stats);
		arena_stats_add_u64(tsdn, &arena->stats, &decay->stats->npurge,
		    1);
		arena_stats_add_u64(tsdn, &arena->stats,
		    &decay->stats->nmadvise, nmadvise);
		arena_stats_add_u64(tsdn, &arena->stats, &decay->stats->purged,
		    npurged);
		arena_stats_sub_zu(tsdn, &arena->stats, &arena->stats.mapped,
		    nunmapped << LG_PAGE);
		arena_stats_unlock(tsdn, &arena->stats);
	}

	return npurged;
}
