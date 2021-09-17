static size_t
do_get_size_impl(const char *cmd, unsigned arena_ind) {
	size_t mib[4];
	size_t miblen = sizeof(mib) / sizeof(size_t);
	size_t z = sizeof(size_t);

	assert_d_eq(mallctlnametomib(cmd, mib, &miblen),
	    0, "Unexpected mallctlnametomib(\"%s\", ...) failure", cmd);
	mib[2] = arena_ind;
	size_t size;
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&size, &z, NULL, 0),
	    0, "Unexpected mallctlbymib([\"%s\"], ...) failure", cmd);

	return size;
}
