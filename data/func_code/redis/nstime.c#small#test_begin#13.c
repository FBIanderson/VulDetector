TEST_END

TEST_BEGIN(test_nstime_init2) {
	nstime_t nst;

	nstime_init2(&nst, 42, 43);
	assert_u64_eq(nstime_sec(&nst), 42, "sec incorrectly read");
	assert_u64_eq(nstime_nsec(&nst), 43, "nsec incorrectly read");
}
