void *
malloc_tsd_malloc(size_t size) {
	return a0malloc(CACHELINE_CEILING(size));
}
