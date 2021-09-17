base_t *
base_new(tsdn_t *tsdn, unsigned ind, extent_hooks_t *extent_hooks) {
	pszind_t pind_last = 0;
	size_t extent_sn_next = 0;
	base_block_t *block = base_block_alloc(tsdn, NULL, extent_hooks, ind,
	    &pind_last, &extent_sn_next, sizeof(base_t), QUANTUM);
	if (block == NULL) {
		return NULL;
	}

	size_t gap_size;
	size_t base_alignment = CACHELINE;
	size_t base_size = ALIGNMENT_CEILING(sizeof(base_t), base_alignment);
	base_t *base = (base_t *)base_extent_bump_alloc_helper(&block->extent,
	    &gap_size, base_size, base_alignment);
	base->ind = ind;
	atomic_store_p(&base->extent_hooks, extent_hooks, ATOMIC_RELAXED);
	if (malloc_mutex_init(&base->mtx, "base", WITNESS_RANK_BASE,
	    malloc_mutex_rank_exclusive)) {
		base_unmap(tsdn, extent_hooks, ind, block, block->size);
		return NULL;
	}
	base->pind_last = pind_last;
	base->extent_sn_next = extent_sn_next;
	base->blocks = block;
	base->auto_thp_switched = false;
	for (szind_t i = 0; i < NSIZES; i++) {
		extent_heap_new(&base->avail[i]);
	}
	if (config_stats) {
		base->allocated = sizeof(base_block_t);
		base->resident = PAGE_CEILING(sizeof(base_block_t));
		base->mapped = block->size;
		base->n_thp = (opt_metadata_thp == metadata_thp_always) &&
		    metadata_thp_madvise() ? HUGEPAGE_CEILING(sizeof(base_block_t))
		    >> LG_HUGEPAGE : 0;
		assert(base->allocated <= base->resident);
		assert(base->resident <= base->mapped);
		assert(base->n_thp << LG_HUGEPAGE <= base->mapped);
	}
	base_extent_bump_alloc_post(base, &block->extent, gap_size, base,
	    base_size);

	return base;
}
