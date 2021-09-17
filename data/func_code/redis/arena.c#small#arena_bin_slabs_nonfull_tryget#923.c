static extent_t *
arena_bin_slabs_nonfull_tryget(bin_t *bin) {
	extent_t *slab = extent_heap_remove_first(&bin->slabs_nonfull);
	if (slab == NULL) {
		return NULL;
	}
	if (config_stats) {
		bin->stats.reslabs++;
	}
	return slab;
}
