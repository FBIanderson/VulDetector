void
large_dalloc_prep_junked_locked(tsdn_t *tsdn, extent_t *extent) {
	large_dalloc_prep_impl(tsdn, extent_arena_get(extent), extent, true);
}
