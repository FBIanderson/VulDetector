static void *
base_alloc_impl(tsdn_t *tsdn, base_t *base, size_t size, size_t alignment,
    size_t *esn) {
	alignment = QUANTUM_CEILING(alignment);
	size_t usize = ALIGNMENT_CEILING(size, alignment);
	size_t asize = usize + alignment - QUANTUM;

	extent_t *extent = NULL;
	malloc_mutex_lock(tsdn, &base->mtx);
	for (szind_t i = sz_size2index(asize); i < NSIZES; i++) {
		extent = extent_heap_remove_first(&base->avail[i]);
		if (extent != NULL) {
			/* Use existing space. */
			break;
		}
	}
	if (extent == NULL) {
		/* Try to allocate more space. */
		extent = base_extent_alloc(tsdn, base, usize, alignment);
	}
	void *ret;
	if (extent == NULL) {
		ret = NULL;
		goto label_return;
	}

	ret = base_extent_bump_alloc(base, extent, usize, alignment);
	if (esn != NULL) {
		*esn = extent_sn_get(extent);
	}
label_return:
	malloc_mutex_unlock(tsdn, &base->mtx);
	return ret;
}
