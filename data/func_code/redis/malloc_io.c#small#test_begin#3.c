TEST_BEGIN(test_malloc_strtoumax_no_endptr) {
	int err;

	set_errno(0);
	assert_ju_eq(malloc_strtoumax("0", NULL, 0), 0, "Unexpected result");
	err = get_errno();
	assert_d_eq(err, 0, "Unexpected failure");
}
