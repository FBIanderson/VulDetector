void *
thd_start(void *arg) {
	unsigned main_arena_ind = *(unsigned *)arg;
	void *p;
	unsigned arena_ind;
	size_t size;
	int err;

	p = malloc(1);
	assert_ptr_not_null(p, "Error in malloc()");
	free(p);

	size = sizeof(arena_ind);
	if ((err = mallctl("thread.arena", (void *)&arena_ind, &size,
	    (void *)&main_arena_ind, sizeof(main_arena_ind)))) {
		char buf[BUFERROR_BUF];

		buferror(err, buf, sizeof(buf));
		test_fail("Error in mallctl(): %s", buf);
	}

	size = sizeof(arena_ind);
	if ((err = mallctl("thread.arena", (void *)&arena_ind, &size, NULL,
	    0))) {
		char buf[BUFERROR_BUF];

		buferror(err, buf, sizeof(buf));
		test_fail("Error in mallctl(): %s", buf);
	}
	assert_u_eq(arena_ind, main_arena_ind,
	    "Arena index should be same as for main thread");

	return NULL;
}
