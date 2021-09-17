TEST_BEGIN(test_alignment_errors) {
	size_t alignment;
	void *p;

	alignment = 0;
	set_errno(0);
	p = aligned_alloc(alignment, 1);
	assert_false(p != NULL || get_errno() != EINVAL,
	    "Expected error for invalid alignment %zu", alignment);

	for (alignment = sizeof(size_t); alignment < MAXALIGN;
	    alignment <<= 1) {
		set_errno(0);
		p = aligned_alloc(alignment + 1, 1);
		assert_false(p != NULL || get_errno() != EINVAL,
		    "Expected error for invalid alignment %zu",
		    alignment + 1);
	}
}
