static void
extent_destroy_default(extent_hooks_t *extent_hooks, void *addr, size_t size,
    bool committed, unsigned arena_ind) {
	extent_destroy_default_impl(addr, size);
}
