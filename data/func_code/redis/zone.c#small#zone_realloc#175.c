static void *
zone_realloc(malloc_zone_t *zone, void *ptr, size_t size) {
	if (ivsalloc(tsdn_fetch(), ptr) != 0) {
		return je_realloc(ptr, size);
	}

	return realloc(ptr, size);
}
