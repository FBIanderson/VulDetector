static void
arena_bin_slabs_full_insert(arena_t *arena, bin_t *bin, extent_t *slab) {
	assert(extent_nfree_get(slab) == 0);
	/*
	 *  Tracking extents is required by arena_reset, which is not allowed
	 *  for auto arenas.  Bypass this step to avoid touching the extent
	 *  linkage (often results in cache misses) for auto arenas.
	 */
	if (arena_is_auto(arena)) {
		return;
	}
	extent_list_append(&bin->slabs_full, slab);
}
