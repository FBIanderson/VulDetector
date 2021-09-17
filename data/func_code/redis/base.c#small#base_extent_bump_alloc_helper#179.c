static void *
base_extent_bump_alloc_helper(extent_t *extent, size_t *gap_size, size_t size,
    size_t alignment) {
	void *ret;

	assert(alignment == ALIGNMENT_CEILING(alignment, QUANTUM));
	assert(size == ALIGNMENT_CEILING(size, alignment));

	*gap_size = ALIGNMENT_CEILING((uintptr_t)extent_addr_get(extent),
	    alignment) - (uintptr_t)extent_addr_get(extent);
	ret = (void *)((uintptr_t)extent_addr_get(extent) + *gap_size);
	assert(extent_bsize_get(extent) >= *gap_size + size);
	extent_binit(extent, (void *)((uintptr_t)extent_addr_get(extent) +
	    *gap_size + size), extent_bsize_get(extent) - *gap_size - size,
	    extent_sn_get(extent));
	return ret;
}
