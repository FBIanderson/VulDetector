static void
arena_dalloc_bin_slab(tsdn_t *tsdn, arena_t *arena, extent_t *slab,
    bin_t *bin) {
	assert(slab != bin->slabcur);

	malloc_mutex_unlock(tsdn, &bin->lock);
	/******************************/
	arena_slab_dalloc(tsdn, arena, slab);
	/****************************/
	malloc_mutex_lock(tsdn, &bin->lock);
	if (config_stats) {
		bin->stats.curslabs--;
	}
}
