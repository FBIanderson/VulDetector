static extent_t *
arena_bin_nonfull_slab_get(tsdn_t *tsdn, arena_t *arena, bin_t *bin,
    szind_t binind) {
	extent_t *slab;
	const bin_info_t *bin_info;

	/* Look for a usable slab. */
	slab = arena_bin_slabs_nonfull_tryget(bin);
	if (slab != NULL) {
		return slab;
	}
	/* No existing slabs have any space available. */

	bin_info = &bin_infos[binind];

	/* Allocate a new slab. */
	malloc_mutex_unlock(tsdn, &bin->lock);
	/******************************/
	slab = arena_slab_alloc(tsdn, arena, binind, bin_info);
	/********************************/
	malloc_mutex_lock(tsdn, &bin->lock);
	if (slab != NULL) {
		if (config_stats) {
			bin->stats.nslabs++;
			bin->stats.curslabs++;
		}
		return slab;
	}

	/*
	 * arena_slab_alloc() failed, but another thread may have made
	 * sufficient memory available while this one dropped bin->lock above,
	 * so search one more time.
	 */
	slab = arena_bin_slabs_nonfull_tryget(bin);
	if (slab != NULL) {
		return slab;
	}

	return NULL;
}
