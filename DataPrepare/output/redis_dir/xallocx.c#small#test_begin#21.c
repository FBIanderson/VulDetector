TEST_BEGIN(test_same_size) {
	void *p;
	size_t sz, tsz;

	p = mallocx(42, 0);
	assert_ptr_not_null(p, "Unexpected mallocx() error");
	sz = sallocx(p, 0);

	tsz = xallocx(p, sz, 0, 0);
	assert_zu_eq(tsz, sz, "Unexpected size change: %zu --> %zu", sz, tsz);

	dallocx(p, 0);
}
