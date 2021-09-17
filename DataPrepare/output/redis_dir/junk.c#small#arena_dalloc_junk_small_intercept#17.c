static void
arena_dalloc_junk_small_intercept(void *ptr, const bin_info_t *bin_info) {
	size_t i;

	arena_dalloc_junk_small_orig(ptr, bin_info);
	for (i = 0; i < bin_info->reg_size; i++) {
		assert_u_eq(((uint8_t *)ptr)[i], JEMALLOC_FREE_JUNK,
		    "Missing junk fill for byte %zu/%zu of deallocated region",
		    i, bin_info->reg_size);
	}
	if (ptr == watch_for_junking) {
		saw_junking = true;
	}
}
