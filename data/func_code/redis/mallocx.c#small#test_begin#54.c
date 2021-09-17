TEST_BEGIN(test_overflow) {
	size_t largemax;

	largemax = get_large_size(get_nlarge()-1);

	assert_ptr_null(mallocx(largemax+1, 0),
	    "Expected OOM for mallocx(size=%#zx, 0)", largemax+1);

	assert_ptr_null(mallocx(ZU(PTRDIFF_MAX)+1, 0),
	    "Expected OOM for mallocx(size=%#zx, 0)", ZU(PTRDIFF_MAX)+1);

	assert_ptr_null(mallocx(SIZE_T_MAX, 0),
	    "Expected OOM for mallocx(size=%#zx, 0)", SIZE_T_MAX);

	assert_ptr_null(mallocx(1, MALLOCX_ALIGN(ZU(PTRDIFF_MAX)+1)),
	    "Expected OOM for mallocx(size=1, MALLOCX_ALIGN(%#zx))",
	    ZU(PTRDIFF_MAX)+1);
}
