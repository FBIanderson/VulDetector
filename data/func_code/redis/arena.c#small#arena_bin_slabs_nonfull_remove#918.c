static void
arena_bin_slabs_nonfull_remove(bin_t *bin, extent_t *slab) {
	extent_heap_remove(&bin->slabs_nonfull, slab);
}
