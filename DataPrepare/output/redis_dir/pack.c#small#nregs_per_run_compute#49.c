static size_t
nregs_per_run_compute(void) {
	uint32_t nregs;
	size_t sz;
	unsigned binind = binind_compute();
	size_t mib[4];
	size_t miblen = sizeof(mib)/sizeof(size_t);

	assert_d_eq(mallctlnametomib("arenas.bin.0.nregs", mib, &miblen), 0,
	    "Unexpected mallctlnametomb failure");
	mib[2] = (size_t)binind;
	sz = sizeof(nregs);
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&nregs, &sz, NULL,
	    0), 0, "Unexpected mallctlbymib failure");
	return nregs;
}
