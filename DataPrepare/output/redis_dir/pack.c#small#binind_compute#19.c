static unsigned
binind_compute(void) {
	size_t sz;
	unsigned nbins, i;

	sz = sizeof(nbins);
	assert_d_eq(mallctl("arenas.nbins", (void *)&nbins, &sz, NULL, 0), 0,
	    "Unexpected mallctl failure");

	for (i = 0; i < nbins; i++) {
		size_t mib[4];
		size_t miblen = sizeof(mib)/sizeof(size_t);
		size_t size;

		assert_d_eq(mallctlnametomib("arenas.bin.0.size", mib,
		    &miblen), 0, "Unexpected mallctlnametomb failure");
		mib[2] = (size_t)i;

		sz = sizeof(size);
		assert_d_eq(mallctlbymib(mib, miblen, (void *)&size, &sz, NULL,
		    0), 0, "Unexpected mallctlbymib failure");
		if (size == SZ) {
			return i;
		}
	}

	test_fail("Unable to compute nregs_per_run");
	return 0;
}
