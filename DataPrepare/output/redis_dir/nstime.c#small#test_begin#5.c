TEST_BEGIN(test_nstime_init) {
	nstime_t nst;

	nstime_init(&nst, 42000000043);
	assert_u64_eq(nstime_ns(&nst), 42000000043, "ns incorrectly read");
	assert_u64_eq(nstime_sec(&nst), 42, "sec incorrectly read");
	assert_u64_eq(nstime_nsec(&nst), 43, "nsec incorrectly read");
}
