TEST_BEGIN(test_pack) {
	bool prof_enabled;
	size_t sz = sizeof(prof_enabled);
	if (mallctl("opt.prof", (void *)&prof_enabled, &sz, NULL, 0) == 0) {
		test_skip_if(prof_enabled);
	}

	unsigned arena_ind = arenas_create_mallctl();
	size_t nregs_per_run = nregs_per_run_compute();
	size_t nregs = nregs_per_run * NSLABS;
	VARIABLE_ARRAY(void *, ptrs, nregs);
	size_t i, j, offset;

	/* Fill matrix. */
	for (i = offset = 0; i < NSLABS; i++) {
		for (j = 0; j < nregs_per_run; j++) {
			void *p = mallocx(SZ, MALLOCX_ARENA(arena_ind) |
			    MALLOCX_TCACHE_NONE);
			assert_ptr_not_null(p,
			    "Unexpected mallocx(%zu, MALLOCX_ARENA(%u) |"
			    " MALLOCX_TCACHE_NONE) failure, run=%zu, reg=%zu",
			    SZ, arena_ind, i, j);
			ptrs[(i * nregs_per_run) + j] = p;
		}
	}

	/*
	 * Free all but one region of each run, but rotate which region is
	 * preserved, so that subsequent allocations exercise the within-run
	 * layout policy.
	 */
	offset = 0;
	for (i = offset = 0;
	    i < NSLABS;
	    i++, offset = (offset + 1) % nregs_per_run) {
		for (j = 0; j < nregs_per_run; j++) {
			void *p = ptrs[(i * nregs_per_run) + j];
			if (offset == j) {
				continue;
			}
			dallocx(p, MALLOCX_ARENA(arena_ind) |
			    MALLOCX_TCACHE_NONE);
		}
	}

	/*
	 * Logically refill matrix, skipping preserved regions and verifying
	 * that the matrix is unmodified.
	 */
	offset = 0;
	for (i = offset = 0;
	    i < NSLABS;
	    i++, offset = (offset + 1) % nregs_per_run) {
		for (j = 0; j < nregs_per_run; j++) {
			void *p;

			if (offset == j) {
				continue;
			}
			p = mallocx(SZ, MALLOCX_ARENA(arena_ind) |
			    MALLOCX_TCACHE_NONE);
			assert_ptr_eq(p, ptrs[(i * nregs_per_run) + j],
			    "Unexpected refill discrepancy, run=%zu, reg=%zu\n",
			    i, j);
		}
	}

	/* Clean up. */
	arena_reset_mallctl(arena_ind);
}
