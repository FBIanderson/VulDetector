static void *
base_map(tsdn_t *tsdn, extent_hooks_t *extent_hooks, unsigned ind, size_t size) {
	void *addr;
	bool zero = true;
	bool commit = true;

	/* Use huge page sizes and alignment regardless of opt_metadata_thp. */
	assert(size == HUGEPAGE_CEILING(size));
	size_t alignment = HUGEPAGE;
	if (extent_hooks == &extent_hooks_default) {
		addr = extent_alloc_mmap(NULL, size, alignment, &zero, &commit);
	} else {
		/* No arena context as we are creating new arenas. */
		tsd_t *tsd = tsdn_null(tsdn) ? tsd_fetch() : tsdn_tsd(tsdn);
		pre_reentrancy(tsd, NULL);
		addr = extent_hooks->alloc(extent_hooks, NULL, size, alignment,
		    &zero, &commit, ind);
		post_reentrancy(tsd);
	}

	return addr;
}
