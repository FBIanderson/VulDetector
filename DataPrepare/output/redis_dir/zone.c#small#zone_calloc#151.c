static void *
zone_calloc(malloc_zone_t *zone, size_t num, size_t size) {
	return je_calloc(num, size);
}
