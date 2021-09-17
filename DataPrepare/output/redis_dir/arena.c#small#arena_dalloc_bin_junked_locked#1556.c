void
arena_dalloc_bin_junked_locked(tsdn_t *tsdn, arena_t *arena, extent_t *extent,
    void *ptr) {
	arena_dalloc_bin_locked_impl(tsdn, arena, extent, ptr, true);
}
