size_t
large_salloc(tsdn_t *tsdn, const extent_t *extent) {
	return extent_usize_get(extent);
}
