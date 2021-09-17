extent_t *
extent_split_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t size_a,
    szind_t szind_a, bool slab_a, size_t size_b, szind_t szind_b, bool slab_b) {
	return extent_split_impl(tsdn, arena, r_extent_hooks, extent, size_a,
	    szind_a, slab_a, size_b, szind_b, slab_b, false);
}
