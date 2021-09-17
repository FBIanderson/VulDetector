extent_t *
base_alloc_extent(tsdn_t *tsdn, base_t *base) {
	size_t esn;
	extent_t *extent = base_alloc_impl(tsdn, base, sizeof(extent_t),
	    CACHELINE, &esn);
	if (extent == NULL) {
		return NULL;
	}
	extent_esn_set(extent, esn);
	return extent;
}
