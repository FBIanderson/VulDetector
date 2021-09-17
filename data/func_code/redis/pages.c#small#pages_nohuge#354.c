bool
pages_nohuge(void *addr, size_t size) {
	return pages_nohuge_impl(addr, size, true);
}
