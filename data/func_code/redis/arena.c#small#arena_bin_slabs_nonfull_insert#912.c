static void
arena_bin_slabs_nonfull_insert(bin_t *bin, extent_t *slab) {
	assert(extent_nfree_get(slab) > 0);
	extent_heap_insert(&bin->slabs_nonfull, slab);
}
