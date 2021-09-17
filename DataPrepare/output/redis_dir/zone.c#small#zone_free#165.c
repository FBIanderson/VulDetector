static void
zone_free(malloc_zone_t *zone, void *ptr) {
	if (ivsalloc(tsdn_fetch(), ptr) != 0) {
		je_free(ptr);
		return;
	}

	free(ptr);
}
