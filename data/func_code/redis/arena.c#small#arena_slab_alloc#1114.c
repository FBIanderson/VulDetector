static extent_t *
arena_slab_alloc(tsdn_t *tsdn, arena_t *arena, szind_t binind,
    const bin_info_t *bin_info) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	extent_hooks_t *extent_hooks = EXTENT_HOOKS_INITIALIZER;
	szind_t szind = sz_size2index(bin_info->reg_size);
	bool zero = false;
	bool commit = true;
	extent_t *slab = extents_alloc(tsdn, arena, &extent_hooks,
	    &arena->extents_dirty, NULL, bin_info->slab_size, 0, PAGE, true,
	    binind, &zero, &commit);
	if (slab == NULL) {
		slab = extents_alloc(tsdn, arena, &extent_hooks,
		    &arena->extents_muzzy, NULL, bin_info->slab_size, 0, PAGE,
		    true, binind, &zero, &commit);
	}
	if (slab == NULL) {
		slab = arena_slab_alloc_hard(tsdn, arena, &extent_hooks,
		    bin_info, szind);
		if (slab == NULL) {
			return NULL;
		}
	}
	assert(extent_slab_get(slab));

	/* Initialize slab internals. */
	arena_slab_data_t *slab_data = extent_slab_data_get(slab);
	extent_nfree_set(slab, bin_info->nregs);
	bitmap_init(slab_data->bitmap, &bin_info->bitmap_info, false);

	arena_nactive_add(arena, extent_size_get(slab) >> LG_PAGE);

	return slab;
}
