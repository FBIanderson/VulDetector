static void *
zone_memalign(malloc_zone_t *zone, size_t alignment, size_t size) {
	void *ret = NULL; /* Assignment avoids useless compiler warning. */

	je_posix_memalign(&ret, alignment, size);

	return ret;
}
