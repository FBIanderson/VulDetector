bool
extent_purge_lazy_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t offset,
    size_t length) {
	return extent_purge_lazy_impl(tsdn, arena, r_extent_hooks, extent,
	    offset, length, false);
}
