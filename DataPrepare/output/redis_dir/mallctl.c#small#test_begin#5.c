TEST_BEGIN(test_mallctl_errors) {
	uint64_t epoch;
	size_t sz;

	assert_d_eq(mallctl("no_such_name", NULL, NULL, NULL, 0), ENOENT,
	    "mallctl() should return ENOENT for non-existent names");

	assert_d_eq(mallctl("version", NULL, NULL, "0.0.0", strlen("0.0.0")),
	    EPERM, "mallctl() should return EPERM on attempt to write "
	    "read-only value");

	assert_d_eq(mallctl("epoch", NULL, NULL, (void *)&epoch,
	    sizeof(epoch)-1), EINVAL,
	    "mallctl() should return EINVAL for input size mismatch");
	assert_d_eq(mallctl("epoch", NULL, NULL, (void *)&epoch,
	    sizeof(epoch)+1), EINVAL,
	    "mallctl() should return EINVAL for input size mismatch");

	sz = sizeof(epoch)-1;
	assert_d_eq(mallctl("epoch", (void *)&epoch, &sz, NULL, 0), EINVAL,
	    "mallctl() should return EINVAL for output size mismatch");
	sz = sizeof(epoch)+1;
	assert_d_eq(mallctl("epoch", (void *)&epoch, &sz, NULL, 0), EINVAL,
	    "mallctl() should return EINVAL for output size mismatch");
}
