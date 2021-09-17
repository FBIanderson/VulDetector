TEST_BEGIN(test_prof_thread_name_threaded) {
	thd_t thds[NTHREADS];
	unsigned thd_args[NTHREADS];
	unsigned i;

	test_skip_if(!config_prof);

	for (i = 0; i < NTHREADS; i++) {
		thd_args[i] = i;
		thd_create(&thds[i], thd_start, (void *)&thd_args[i]);
	}
	for (i = 0; i < NTHREADS; i++) {
		thd_join(thds[i], NULL);
	}
}
