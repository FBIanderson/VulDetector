bool
pages_commit(void *addr, size_t size) {
	return pages_commit_impl(addr, size, true);
}
