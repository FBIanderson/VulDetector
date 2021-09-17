bool
pages_huge(void *addr, size_t size) {
	return pages_huge_impl(addr, size, true);
}
