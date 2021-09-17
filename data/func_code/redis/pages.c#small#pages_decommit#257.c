bool
pages_decommit(void *addr, size_t size) {
	return pages_commit_impl(addr, size, false);
}
