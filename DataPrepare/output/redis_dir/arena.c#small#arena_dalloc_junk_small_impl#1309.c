static void
arena_dalloc_junk_small_impl(void *ptr, const bin_info_t *bin_info) {
	memset(ptr, JEMALLOC_FREE_JUNK, bin_info->reg_size);
}
