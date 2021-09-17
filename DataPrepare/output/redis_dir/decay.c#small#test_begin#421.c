TEST_BEGIN(test_decay_ticker) {
	test_skip_if(check_background_thread_enabled());
#define NPS 2048
	ssize_t ddt = opt_dirty_decay_ms;
	ssize_t mdt = opt_muzzy_decay_ms;
	unsigned arena_ind = do_arena_create(ddt, mdt);
	int flags = (MALLOCX_ARENA(arena_ind) | MALLOCX_TCACHE_NONE);
	void *ps[NPS];
	size_t large;

	/*
	 * Allocate a bunch of large objects, pause the clock, deallocate every
	 * other object (to fragment virtual memory), restore the clock, then
	 * [md]allocx() in a tight loop while advancing time rapidly to verify
	 * the ticker triggers purging.
	 */

	size_t tcache_max;
	size_t sz = sizeof(size_t);
	assert_d_eq(mallctl("arenas.tcache_max", (void *)&tcache_max, &sz, NULL,
	    0), 0, "Unexpected mallctl failure");
	large = nallocx(tcache_max + 1, flags);

	do_purge(arena_ind);
	uint64_t dirty_npurge0 = get_arena_dirty_npurge(arena_ind);
	uint64_t muzzy_npurge0 = get_arena_muzzy_npurge(arena_ind);

	for (unsigned i = 0; i < NPS; i++) {
		ps[i] = do_mallocx(large, flags);
	}

	nupdates_mock = 0;
	nstime_init(&time_mock, 0);
	nstime_update(&time_mock);
	monotonic_mock = true;

	nstime_monotonic_orig = nstime_monotonic;
	nstime_update_orig = nstime_update;
	nstime_monotonic = nstime_monotonic_mock;
	nstime_update = nstime_update_mock;

	for (unsigned i = 0; i < NPS; i += 2) {
		dallocx(ps[i], flags);
		unsigned nupdates0 = nupdates_mock;
		do_decay(arena_ind);
		assert_u_gt(nupdates_mock, nupdates0,
		    "Expected nstime_update() to be called");
	}

	decay_ticker_helper(arena_ind, flags, true, ddt, dirty_npurge0,
	    muzzy_npurge0, true);
	decay_ticker_helper(arena_ind, flags, false, ddt+mdt, dirty_npurge0,
	    muzzy_npurge0, false);

	do_arena_destroy(arena_ind);

	nstime_monotonic = nstime_monotonic_orig;
	nstime_update = nstime_update_orig;
#undef NPS
}
