TEST_BEGIN(test_background_thread_ctl) {
	test_skip_if(!have_background_thread);

	bool e0, e1;
	size_t sz = sizeof(bool);

	assert_d_eq(mallctl("opt.background_thread", (void *)&e0, &sz,
	    NULL, 0), 0, "Unexpected mallctl() failure");
	assert_d_eq(mallctl("background_thread", (void *)&e1, &sz,
	    NULL, 0), 0, "Unexpected mallctl() failure");
	assert_b_eq(e0, e1,
	    "Default and opt.background_thread does not match.\n");
	if (e0) {
		test_switch_background_thread_ctl(false);
	}
	assert_zu_eq(n_background_threads, 0,
	    "Number of background threads should be 0.\n");

	for (unsigned i = 0; i < 4; i++) {
		test_switch_background_thread_ctl(true);
		test_repeat_background_thread_ctl(true);
		test_repeat_background_thread_ctl(true);

		test_switch_background_thread_ctl(false);
		test_repeat_background_thread_ctl(false);
		test_repeat_background_thread_ctl(false);
	}
}
