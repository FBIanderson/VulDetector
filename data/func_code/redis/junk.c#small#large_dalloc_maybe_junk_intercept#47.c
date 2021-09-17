static void
large_dalloc_maybe_junk_intercept(void *ptr, size_t usize) {
	large_dalloc_maybe_junk_orig(ptr, usize);
	if (ptr == watch_for_junking) {
		saw_junking = true;
	}
}
