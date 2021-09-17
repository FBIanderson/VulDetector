TEST_BEGIN(test_zero_small) {
	test_skip_if(!config_fill);
	test_zero(1, SMALL_MAXCLASS-1);
}
