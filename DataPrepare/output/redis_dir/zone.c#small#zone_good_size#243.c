static size_t
zone_good_size(malloc_zone_t *zone, size_t size) {
	if (size == 0) {
		size = 1;
	}
	return sz_s2u(size);
}
