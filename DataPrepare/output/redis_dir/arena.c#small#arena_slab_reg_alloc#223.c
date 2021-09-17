static void *
arena_slab_reg_alloc(extent_t *slab, const bin_info_t *bin_info) {
	void *ret;
	arena_slab_data_t *slab_data = extent_slab_data_get(slab);
	size_t regind;

	assert(extent_nfree_get(slab) > 0);
	assert(!bitmap_full(slab_data->bitmap, &bin_info->bitmap_info));

	regind = bitmap_sfu(slab_data->bitmap, &bin_info->bitmap_info);
	ret = (void *)((uintptr_t)extent_addr_get(slab) +
	    (uintptr_t)(bin_info->reg_size * regind));
	extent_nfree_dec(slab);
	return ret;
}
