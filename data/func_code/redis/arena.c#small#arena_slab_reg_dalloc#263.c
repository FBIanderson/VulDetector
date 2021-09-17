static void
arena_slab_reg_dalloc(extent_t *slab, arena_slab_data_t *slab_data, void *ptr) {
	szind_t binind = extent_szind_get(slab);
	const bin_info_t *bin_info = &bin_infos[binind];
	size_t regind = arena_slab_regind(slab, binind, ptr);

	assert(extent_nfree_get(slab) < bin_info->nregs);
	/* Freeing an unallocated pointer can cause assertion failure. */
	assert(bitmap_get(slab_data->bitmap, &bin_info->bitmap_info, regind));

	bitmap_unset(slab_data->bitmap, &bin_info->bitmap_info, regind);
	extent_nfree_inc(slab);
}
