static void
zone_free_definite_size(malloc_zone_t *zone, void *ptr, size_t size) {
	size_t alloc_size;

	alloc_size = ivsalloc(tsdn_fetch(), ptr);
	if (alloc_size != 0) {
		assert(alloc_size == size);
		je_free(ptr);
		return;
	}

	free(ptr);
}
