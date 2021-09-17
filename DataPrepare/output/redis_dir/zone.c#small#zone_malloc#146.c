static void *
zone_malloc(malloc_zone_t *zone, size_t size) {
	return je_malloc(size);
}
