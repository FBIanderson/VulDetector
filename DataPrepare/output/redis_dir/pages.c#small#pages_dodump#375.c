bool
pages_dodump(void *addr, size_t size) {
	assert(PAGE_ADDR2BASE(addr) == addr);
	assert(PAGE_CEILING(size) == size);
#ifdef JEMALLOC_MADVISE_DONTDUMP
	return madvise(addr, size, MADV_DODUMP) != 0;
#else
	return false;
#endif
}
