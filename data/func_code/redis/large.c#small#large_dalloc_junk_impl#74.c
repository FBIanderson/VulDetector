static void
large_dalloc_junk_impl(void *ptr, size_t size) {
	memset(ptr, JEMALLOC_FREE_JUNK, size);
}
