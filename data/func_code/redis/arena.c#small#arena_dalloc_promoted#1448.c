void
arena_dalloc_promoted(tsdn_t *tsdn, void *ptr, tcache_t *tcache,
    bool slow_path) {
	cassert(config_prof);
	assert(opt_prof);

	extent_t *extent = iealloc(tsdn, ptr);
	size_t usize = arena_prof_demote(tsdn, extent, ptr);
	if (usize <= tcache_maxclass) {
		tcache_dalloc_large(tsdn_tsd(tsdn), tcache, ptr,
		    sz_size2index(usize), slow_path);
	} else {
		large_dalloc(tsdn, extent);
	}
}
