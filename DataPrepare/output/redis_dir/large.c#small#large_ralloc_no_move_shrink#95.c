static bool
large_ralloc_no_move_shrink(tsdn_t *tsdn, extent_t *extent, size_t usize) {
	arena_t *arena = extent_arena_get(extent);
	size_t oldusize = extent_usize_get(extent);
	extent_hooks_t *extent_hooks = extent_hooks_get(arena);
	size_t diff = extent_size_get(extent) - (usize + sz_large_pad);

	assert(oldusize > usize);

	if (extent_hooks->split == NULL) {
		return true;
	}

	/* Split excess pages. */
	if (diff != 0) {
		extent_t *trail = extent_split_wrapper(tsdn, arena,
		    &extent_hooks, extent, usize + sz_large_pad,
		    sz_size2index(usize), false, diff, NSIZES, false);
		if (trail == NULL) {
			return true;
		}

		if (config_fill && unlikely(opt_junk_free)) {
			large_dalloc_maybe_junk(extent_addr_get(trail),
			    extent_size_get(trail));
		}

		arena_extents_dirty_dalloc(tsdn, arena, &extent_hooks, trail);
	}

	arena_extent_ralloc_large_shrink(tsdn, arena, extent, oldusize);

	return false;
}
