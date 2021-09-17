static void *
base_extent_bump_alloc(base_t *base, extent_t *extent, size_t size,
    size_t alignment) {
	void *ret;
	size_t gap_size;

	ret = base_extent_bump_alloc_helper(extent, &gap_size, size, alignment);
	base_extent_bump_alloc_post(base, extent, gap_size, ret, size);
	return ret;
}
