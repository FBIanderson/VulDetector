static void
arena_dalloc_bin_locked_impl(tsdn_t *tsdn, arena_t *arena, extent_t *slab,
    void *ptr, bool junked) {
	arena_slab_data_t *slab_data = extent_slab_data_get(slab);
	szind_t binind = extent_szind_get(slab);
	bin_t *bin = &arena->bins[binind];
	const bin_info_t *bin_info = &bin_infos[binind];

	if (!junked && config_fill && unlikely(opt_junk_free)) {
		arena_dalloc_junk_small(ptr, bin_info);
	}

	arena_slab_reg_dalloc(slab, slab_data, ptr);
	unsigned nfree = extent_nfree_get(slab);
	if (nfree == bin_info->nregs) {
		arena_dissociate_bin_slab(arena, slab, bin);
		arena_dalloc_bin_slab(tsdn, arena, slab, bin);
	} else if (nfree == 1 && slab != bin->slabcur) {
		arena_bin_slabs_full_remove(arena, bin, slab);
		arena_bin_lower_slab(tsdn, arena, slab, bin);
	}

	if (config_stats) {
		bin->stats.ndalloc++;
		bin->stats.curregs--;
	}
}
