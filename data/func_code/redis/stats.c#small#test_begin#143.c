TEST_BEGIN(test_stats_arenas_small) {
	void *p;
	size_t sz, allocated;
	uint64_t epoch, nmalloc, ndalloc, nrequests;
	int expected = config_stats ? 0 : ENOENT;

	no_lazy_lock(); /* Lazy locking would dodge tcache testing. */

	p = mallocx(SMALL_MAXCLASS, MALLOCX_ARENA(0));
	assert_ptr_not_null(p, "Unexpected mallocx() failure");

	assert_d_eq(mallctl("thread.tcache.flush", NULL, NULL, NULL, 0),
	    opt_tcache ? 0 : EFAULT, "Unexpected mallctl() result");

	assert_d_eq(mallctl("epoch", NULL, NULL, (void *)&epoch, sizeof(epoch)),
	    0, "Unexpected mallctl() failure");

	sz = sizeof(size_t);
	assert_d_eq(mallctl("stats.arenas.0.small.allocated",
	    (void *)&allocated, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");
	sz = sizeof(uint64_t);
	assert_d_eq(mallctl("stats.arenas.0.small.nmalloc", (void *)&nmalloc,
	    &sz, NULL, 0), expected, "Unexpected mallctl() result");
	assert_d_eq(mallctl("stats.arenas.0.small.ndalloc", (void *)&ndalloc,
	    &sz, NULL, 0), expected, "Unexpected mallctl() result");
	assert_d_eq(mallctl("stats.arenas.0.small.nrequests",
	    (void *)&nrequests, &sz, NULL, 0), expected,
	    "Unexpected mallctl() result");

	if (config_stats) {
		assert_zu_gt(allocated, 0,
		    "allocated should be greater than zero");
		assert_u64_gt(nmalloc, 0,
		    "nmalloc should be no greater than zero");
		assert_u64_ge(nmalloc, ndalloc,
		    "nmalloc should be at least as large as ndalloc");
		assert_u64_gt(nrequests, 0,
		    "nrequests should be greater than zero");
	}

	dallocx(p, 0);
}
