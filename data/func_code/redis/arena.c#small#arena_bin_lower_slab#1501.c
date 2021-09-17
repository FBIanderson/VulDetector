static void
arena_bin_lower_slab(UNUSED tsdn_t *tsdn, arena_t *arena, extent_t *slab,
    bin_t *bin) {
	assert(extent_nfree_get(slab) > 0);

	/*
	 * Make sure that if bin->slabcur is non-NULL, it refers to the
	 * oldest/lowest non-full slab.  It is okay to NULL slabcur out rather
	 * than proactively keeping it pointing at the oldest/lowest non-full
	 * slab.
	 */
	if (bin->slabcur != NULL && extent_snad_comp(bin->slabcur, slab) > 0) {
		/* Switch slabcur. */
		if (extent_nfree_get(bin->slabcur) > 0) {
			arena_bin_slabs_nonfull_insert(bin, bin->slabcur);
		} else {
			arena_bin_slabs_full_insert(arena, bin, bin->slabcur);
		}
		bin->slabcur = slab;
		if (config_stats) {
			bin->stats.reslabs++;
		}
	} else {
		arena_bin_slabs_nonfull_insert(bin, slab);
	}
}
