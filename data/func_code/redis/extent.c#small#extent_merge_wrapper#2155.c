bool
extent_merge_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *a, extent_t *b) {
	return extent_merge_impl(tsdn, arena, r_extent_hooks, a, b, false);
}
