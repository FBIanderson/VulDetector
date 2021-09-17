TEST_BEGIN(test_zero_large) {
	size_t large0, large1;

	/* Get size classes. */
	large0 = get_large_size(0);
	large1 = get_large_size(1);

	test_zero(large1, large0 * 2);
}
