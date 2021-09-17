static bool
extent_commit_default(extent_hooks_t *extent_hooks, void *addr, size_t size,
    size_t offset, size_t length, unsigned arena_ind) {
	return pages_commit((void *)((uintptr_t)addr + (uintptr_t)offset),
	    length);
}
