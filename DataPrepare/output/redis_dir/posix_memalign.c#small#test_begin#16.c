TEST_BEGIN(test_alignment_errors) {
	size_t alignment;
	void *p;

	for (alignment = 0; alignment < sizeof(void *); alignment++) {
		assert_d_eq(posix_memalign(&p, alignment, 1), EINVAL,
		    "Expected error for invalid alignment %zu",
		    alignment);
	}

	for (alignment = sizeof(size_t); alignment < MAXALIGN;
	    alignment <<= 1) {
		assert_d_ne(posix_memalign(&p, alignment + 1, 1), 0,
		    "Expected error for invalid alignment %zu",
		    alignment + 1);
	}
}
