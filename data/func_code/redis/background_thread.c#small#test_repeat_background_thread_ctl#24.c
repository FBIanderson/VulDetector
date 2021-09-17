static void
test_repeat_background_thread_ctl(bool before) {
	bool e0, e1;
	size_t sz = sizeof(bool);

	e1 = before;
	assert_d_eq(mallctl("background_thread", (void *)&e0, &sz,
	    &e1, sz), 0, "Unexpected mallctl() failure");
	assert_b_eq(e0, before,
	    "background_thread should be %d.\n", before);
	if (e1) {
		assert_zu_gt(n_background_threads, 0,
		    "Number of background threads should be non zero.\n");
	} else {
		assert_zu_eq(n_background_threads, 0,
		    "Number of background threads should be zero.\n");
	}
}
