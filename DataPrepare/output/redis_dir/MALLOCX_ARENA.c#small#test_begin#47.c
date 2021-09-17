TEST_BEGIN(test_MALLOCX_ARENA) {
	thd_t thds[NTHREADS];
	unsigned i;

	for (i = 0; i < NTHREADS; i++) {
		thd_create(&thds[i], thd_start,
		    (void *)(uintptr_t)i);
	}

	for (i = 0; i < NTHREADS; i++) {
		thd_join(thds[i], NULL);
	}
}
