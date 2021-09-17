static size_t
get_max_size_class(void) {
	unsigned nlextents;
	size_t mib[4];
	size_t sz, miblen, max_size_class;

	sz = sizeof(unsigned);
	assert_d_eq(mallctl("arenas.nlextents", (void *)&nlextents, &sz, NULL,
	    0), 0, "Unexpected mallctl() error");

	miblen = sizeof(mib) / sizeof(size_t);
	assert_d_eq(mallctlnametomib("arenas.lextent.0.size", mib, &miblen), 0,
	    "Unexpected mallctlnametomib() error");
	mib[2] = nlextents - 1;

	sz = sizeof(size_t);
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&max_size_class, &sz,
	    NULL, 0), 0, "Unexpected mallctlbymib() error");

	return max_size_class;
}
