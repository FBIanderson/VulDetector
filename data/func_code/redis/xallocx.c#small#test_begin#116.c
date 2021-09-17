TEST_BEGIN(test_size) {
	size_t small0, largemax;
	void *p;

	/* Get size classes. */
	small0 = get_small_size(0);
	largemax = get_large_size(get_nlarge()-1);

	p = mallocx(small0, 0);
	assert_ptr_not_null(p, "Unexpected mallocx() error");

	/* Test smallest supported size. */
	assert_zu_eq(xallocx(p, 1, 0, 0), small0,
	    "Unexpected xallocx() behavior");

	/* Test largest supported size. */
	assert_zu_le(xallocx(p, largemax, 0, 0), largemax,
	    "Unexpected xallocx() behavior");

	/* Test size overflow. */
	assert_zu_le(xallocx(p, largemax+1, 0, 0), largemax,
	    "Unexpected xallocx() behavior");
	assert_zu_le(xallocx(p, SIZE_T_MAX, 0, 0), largemax,
	    "Unexpected xallocx() behavior");

	dallocx(p, 0);
}
