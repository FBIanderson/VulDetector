static void
test_extent_body(unsigned arena_ind) {
	void *p;
	size_t large0, large1, large2, sz;
	size_t purge_mib[3];
	size_t purge_miblen;
	int flags;
	bool xallocx_success_a, xallocx_success_b, xallocx_success_c;

	flags = MALLOCX_ARENA(arena_ind) | MALLOCX_TCACHE_NONE;

	/* Get large size classes. */
	sz = sizeof(size_t);
	assert_d_eq(mallctl("arenas.lextent.0.size", (void *)&large0, &sz, NULL,
	    0), 0, "Unexpected arenas.lextent.0.size failure");
	assert_d_eq(mallctl("arenas.lextent.1.size", (void *)&large1, &sz, NULL,
	    0), 0, "Unexpected arenas.lextent.1.size failure");
	assert_d_eq(mallctl("arenas.lextent.2.size", (void *)&large2, &sz, NULL,
	    0), 0, "Unexpected arenas.lextent.2.size failure");

	/* Test dalloc/decommit/purge cascade. */
	purge_miblen = sizeof(purge_mib)/sizeof(size_t);
	assert_d_eq(mallctlnametomib("arena.0.purge", purge_mib, &purge_miblen),
	    0, "Unexpected mallctlnametomib() failure");
	purge_mib[1] = (size_t)arena_ind;
	called_alloc = false;
	try_alloc = true;
	try_dalloc = false;
	try_decommit = false;
	p = mallocx(large0 * 2, flags);
	assert_ptr_not_null(p, "Unexpected mallocx() error");
	assert_true(called_alloc, "Expected alloc call");
	called_dalloc = false;
	called_decommit = false;
	did_purge_lazy = false;
	did_purge_forced = false;
	called_split = false;
	xallocx_success_a = (xallocx(p, large0, 0, flags) == large0);
	assert_d_eq(mallctlbymib(purge_mib, purge_miblen, NULL, NULL, NULL, 0),
	    0, "Unexpected arena.%u.purge error", arena_ind);
	if (xallocx_success_a) {
		assert_true(called_dalloc, "Expected dalloc call");
		assert_true(called_decommit, "Expected decommit call");
		assert_true(did_purge_lazy || did_purge_forced,
		    "Expected purge");
	}
	assert_true(called_split, "Expected split call");
	dallocx(p, flags);
	try_dalloc = true;

	/* Test decommit/commit and observe split/merge. */
	try_dalloc = false;
	try_decommit = true;
	p = mallocx(large0 * 2, flags);
	assert_ptr_not_null(p, "Unexpected mallocx() error");
	did_decommit = false;
	did_commit = false;
	called_split = false;
	did_split = false;
	did_merge = false;
	xallocx_success_b = (xallocx(p, large0, 0, flags) == large0);
	assert_d_eq(mallctlbymib(purge_mib, purge_miblen, NULL, NULL, NULL, 0),
	    0, "Unexpected arena.%u.purge error", arena_ind);
	if (xallocx_success_b) {
		assert_true(did_split, "Expected split");
	}
	xallocx_success_c = (xallocx(p, large0 * 2, 0, flags) == large0 * 2);
	if (did_split) {
		assert_b_eq(did_decommit, did_commit,
		    "Expected decommit/commit match");
	}
	if (xallocx_success_b && xallocx_success_c) {
		assert_true(did_merge, "Expected merge");
	}
	dallocx(p, flags);
	try_dalloc = true;
	try_decommit = false;

	/* Make sure non-large allocation succeeds. */
	p = mallocx(42, flags);
	assert_ptr_not_null(p, "Unexpected mallocx() error");
	dallocx(p, flags);
}
