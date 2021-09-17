static bool
pages_huge_unaligned(void *addr, size_t size) {
	return pages_huge_impl(addr, size, false);
}
