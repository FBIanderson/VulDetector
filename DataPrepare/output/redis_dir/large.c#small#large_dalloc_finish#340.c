void
large_dalloc_finish(tsdn_t *tsdn, extent_t *extent) {
	large_dalloc_finish_impl(tsdn, extent_arena_get(extent), extent);
}
