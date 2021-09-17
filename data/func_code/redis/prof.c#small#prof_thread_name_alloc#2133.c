static char *
prof_thread_name_alloc(tsdn_t *tsdn, const char *thread_name) {
	char *ret;
	size_t size;

	if (thread_name == NULL) {
		return NULL;
	}

	size = strlen(thread_name) + 1;
	if (size == 1) {
		return "";
	}

	ret = iallocztm(tsdn, size, sz_size2index(size), false, NULL, true,
	    arena_get(TSDN_NULL, 0, true), true);
	if (ret == NULL) {
		return NULL;
	}
	memcpy(ret, thread_name, size);
	return ret;
}
