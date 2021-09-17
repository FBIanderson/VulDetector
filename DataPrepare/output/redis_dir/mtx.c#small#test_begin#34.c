TEST_BEGIN(test_mtx_race) {
	thd_start_arg_t arg;
	thd_t thds[NTHREADS];
	unsigned i;

	assert_false(mtx_init(&arg.mtx), "Unexpected mtx_init() failure");
	arg.x = 0;
	for (i = 0; i < NTHREADS; i++) {
		thd_create(&thds[i], thd_start, (void *)&arg);
	}
	for (i = 0; i < NTHREADS; i++) {
		thd_join(thds[i], NULL);
	}
	assert_u_eq(arg.x, NTHREADS * NINCRS,
	    "Race-related counter corruption");
}
