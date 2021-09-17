TEST_BEGIN(test_junk_small) {
	test_skip_if(!config_fill);
	test_junk(1, SMALL_MAXCLASS-1);
}
