static void
do_arena_reset_post(void **ptrs, unsigned nptrs, unsigned arena_ind) {
	tsdn_t *tsdn;
	unsigned i;

	tsdn = tsdn_fetch();

	if (have_background_thread) {
		malloc_mutex_lock(tsdn,
		    &background_thread_info[arena_ind % ncpus].mtx);
	}
	/* Verify allocations no longer exist. */
	for (i = 0; i < nptrs; i++) {
		assert_zu_eq(vsalloc(tsdn, ptrs[i]), 0,
		    "Allocation should no longer exist");
	}
	if (have_background_thread) {
		malloc_mutex_unlock(tsdn,
		    &background_thread_info[arena_ind % ncpus].mtx);
	}

	free(ptrs);
}
