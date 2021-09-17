static void
large_dalloc_junk_intercept(void *ptr, size_t usize) {
	size_t i;

	large_dalloc_junk_orig(ptr, usize);
	for (i = 0; i < usize; i++) {
		assert_u_eq(((uint8_t *)ptr)[i], JEMALLOC_FREE_JUNK,
		    "Missing junk fill for byte %zu/%zu of deallocated region",
		    i, usize);
	}
	if (ptr == watch_for_junking) {
		saw_junking = true;
	}
}
