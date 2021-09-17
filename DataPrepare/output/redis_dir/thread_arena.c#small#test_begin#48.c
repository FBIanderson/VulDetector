TEST_BEGIN(test_thread_arena) {
	void *p;
	int err;
	thd_t thds[NTHREADS];
	unsigned i;

	p = malloc(1);
	assert_ptr_not_null(p, "Error in malloc()");

	unsigned arena_ind, old_arena_ind;
	size_t sz = sizeof(unsigned);
	assert_d_eq(mallctl("arenas.create", (void *)&arena_ind, &sz, NULL, 0),
	    0, "Arena creation failure");

	size_t size = sizeof(arena_ind);
	if ((err = mallctl("thread.arena", (void *)&old_arena_ind, &size,
	    (void *)&arena_ind, sizeof(arena_ind))) != 0) {
		mallctl_failure(err);
	}

	for (i = 0; i < NTHREADS; i++) {
		thd_create(&thds[i], thd_start,
		    (void *)&arena_ind);
	}

	for (i = 0; i < NTHREADS; i++) {
		intptr_t join_ret;
		thd_join(thds[i], (void *)&join_ret);
		assert_zd_eq(join_ret, 0, "Unexpected thread join error");
	}
	free(p);
}
