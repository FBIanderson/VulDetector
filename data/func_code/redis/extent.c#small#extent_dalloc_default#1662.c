static bool
extent_dalloc_default(extent_hooks_t *extent_hooks, void *addr, size_t size,
    bool committed, unsigned arena_ind) {
	return extent_dalloc_default_impl(addr, size);
}
