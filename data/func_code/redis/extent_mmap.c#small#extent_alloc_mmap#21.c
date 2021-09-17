void *
extent_alloc_mmap(void *new_addr, size_t size, size_t alignment, bool *zero,
    bool *commit) {
	void *ret = pages_map(new_addr, size, ALIGNMENT_CEILING(alignment,
	    PAGE), commit);
	if (ret == NULL) {
		return NULL;
	}
	assert(ret != NULL);
	if (*commit) {
		*zero = true;
	}
	return ret;
}
