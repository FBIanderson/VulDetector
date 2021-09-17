TEST_BEGIN(test_prof_reset_cleanup) {
	void *p;
	prof_dump_header_t *prof_dump_header_orig;

	test_skip_if(!config_prof);

	set_prof_active(true);

	assert_zu_eq(prof_bt_count(), 0, "Expected 0 backtraces");
	p = mallocx(1, 0);
	assert_ptr_not_null(p, "Unexpected mallocx() failure");
	assert_zu_eq(prof_bt_count(), 1, "Expected 1 backtrace");

	prof_dump_header_orig = prof_dump_header;
	prof_dump_header = prof_dump_header_intercept;
	assert_false(prof_dump_header_intercepted, "Unexpected intercept");

	assert_d_eq(mallctl("prof.dump", NULL, NULL, NULL, 0),
	    0, "Unexpected error while dumping heap profile");
	assert_true(prof_dump_header_intercepted, "Expected intercept");
	assert_u64_eq(cnt_all_copy.curobjs, 1, "Expected 1 allocation");

	assert_d_eq(mallctl("prof.reset", NULL, NULL, NULL, 0), 0,
	    "Unexpected error while resetting heap profile data");
	assert_d_eq(mallctl("prof.dump", NULL, NULL, NULL, 0),
	    0, "Unexpected error while dumping heap profile");
	assert_u64_eq(cnt_all_copy.curobjs, 0, "Expected 0 allocations");
	assert_zu_eq(prof_bt_count(), 1, "Expected 1 backtrace");

	prof_dump_header = prof_dump_header_orig;

	dallocx(p, 0);
	assert_zu_eq(prof_bt_count(), 0, "Expected 0 backtraces");

	set_prof_active(false);
}
