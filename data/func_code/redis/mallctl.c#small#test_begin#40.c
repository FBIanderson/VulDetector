TEST_END

TEST_BEGIN(test_mallctlbymib_errors) {
	uint64_t epoch;
	size_t sz;
	size_t mib[1];
	size_t miblen;

	miblen = sizeof(mib)/sizeof(size_t);
	assert_d_eq(mallctlnametomib("version", mib, &miblen), 0,
	    "Unexpected mallctlnametomib() failure");

	assert_d_eq(mallctlbymib(mib, miblen, NULL, NULL, "0.0.0",
	    strlen("0.0.0")), EPERM, "mallctl() should return EPERM on "
	    "attempt to write read-only value");

	miblen = sizeof(mib)/sizeof(size_t);
	assert_d_eq(mallctlnametomib("epoch", mib, &miblen), 0,
	    "Unexpected mallctlnametomib() failure");

	assert_d_eq(mallctlbymib(mib, miblen, NULL, NULL, (void *)&epoch,
	    sizeof(epoch)-1), EINVAL,
	    "mallctlbymib() should return EINVAL for input size mismatch");
	assert_d_eq(mallctlbymib(mib, miblen, NULL, NULL, (void *)&epoch,
	    sizeof(epoch)+1), EINVAL,
	    "mallctlbymib() should return EINVAL for input size mismatch");

	sz = sizeof(epoch)-1;
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&epoch, &sz, NULL, 0),
	    EINVAL,
	    "mallctlbymib() should return EINVAL for output size mismatch");
	sz = sizeof(epoch)+1;
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&epoch, &sz, NULL, 0),
	    EINVAL,
	    "mallctlbymib() should return EINVAL for output size mismatch");
}
