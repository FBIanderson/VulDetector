static void
test_zero(size_t szmin, size_t szmax) {
	int flags = MALLOCX_ARENA(arena_ind()) | MALLOCX_ZERO;
	size_t sz, nsz;
	void *p;
#define FILL_BYTE 0x7aU

	sz = szmax;
	p = mallocx(sz, flags);
	assert_ptr_not_null(p, "Unexpected mallocx() error");
	assert_false(validate_fill(p, 0x00, 0, sz), "Memory not filled: sz=%zu",
	    sz);

	/*
	 * Fill with non-zero so that non-debug builds are more likely to detect
	 * errors.
	 */
	memset(p, FILL_BYTE, sz);
	assert_false(validate_fill(p, FILL_BYTE, 0, sz),
	    "Memory not filled: sz=%zu", sz);

	/* Shrink in place so that we can expect growing in place to succeed. */
	sz = szmin;
	if (xallocx(p, sz, 0, flags) != sz) {
		p = rallocx(p, sz, flags);
		assert_ptr_not_null(p, "Unexpected rallocx() failure");
	}
	assert_false(validate_fill(p, FILL_BYTE, 0, sz),
	    "Memory not filled: sz=%zu", sz);

	for (sz = szmin; sz < szmax; sz = nsz) {
		nsz = nallocx(sz+1, flags);
		if (xallocx(p, sz+1, 0, flags) != nsz) {
			p = rallocx(p, sz+1, flags);
			assert_ptr_not_null(p, "Unexpected rallocx() failure");
		}
		assert_false(validate_fill(p, FILL_BYTE, 0, sz),
		    "Memory not filled: sz=%zu", sz);
		assert_false(validate_fill(p, 0x00, sz, nsz-sz),
		    "Memory not filled: sz=%zu, nsz-sz=%zu", sz, nsz-sz);
		memset((void *)((uintptr_t)p + sz), FILL_BYTE, nsz-sz);
		assert_false(validate_fill(p, FILL_BYTE, 0, nsz),
		    "Memory not filled: nsz=%zu", nsz);
	}

	dallocx(p, flags);
}
