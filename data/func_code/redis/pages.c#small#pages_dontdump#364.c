bool
pages_dontdump(void *addr, size_t size) {
	assert(PAGE_ADDR2BASE(addr) == addr);
	assert(PAGE_CEILING(size) == size);
#ifdef JEMALLOC_MADVISE_DONTDUMP
	return madvise(addr, size, MADV_DONTDUMP) != 0;
#else
	return false;
#endif
}
