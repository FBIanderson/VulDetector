TEST_BEGIN(test_zero) {
	void *p, *q;
	size_t psz, qsz, i, j;
	size_t start_sizes[] = {1, 3*1024, 63*1024, 4095*1024};
#define FILL_BYTE 0xaaU
#define RANGE 2048

	for (i = 0; i < sizeof(start_sizes)/sizeof(size_t); i++) {
		size_t start_size = start_sizes[i];
		p = mallocx(start_size, MALLOCX_ZERO);
		assert_ptr_not_null(p, "Unexpected mallocx() error");
		psz = sallocx(p, 0);

		assert_false(validate_fill(p, 0, 0, psz),
		    "Expected zeroed memory");
		memset(p, FILL_BYTE, psz);
		assert_false(validate_fill(p, FILL_BYTE, 0, psz),
		    "Expected filled memory");

		for (j = 1; j < RANGE; j++) {
			q = rallocx(p, start_size+j, MALLOCX_ZERO);
			assert_ptr_not_null(q, "Unexpected rallocx() error");
			qsz = sallocx(q, 0);
			if (q != p || qsz != psz) {
				assert_false(validate_fill(q, FILL_BYTE, 0,
				    psz), "Expected filled memory");
				assert_false(validate_fill(q, 0, psz, qsz-psz),
				    "Expected zeroed memory");
			}
			if (psz != qsz) {
				memset((void *)((uintptr_t)q+psz), FILL_BYTE,
				    qsz-psz);
				psz = qsz;
			}
			p = q;
		}
		assert_false(validate_fill(p, FILL_BYTE, 0, psz),
		    "Expected filled memory");
		dallocx(p, 0);
	}
#undef FILL_BYTE
}
