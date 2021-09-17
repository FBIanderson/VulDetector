static void
mallctl_bool_get(const char *name, bool expected, const char *func, int line) {
	bool old;
	size_t sz;

	sz = sizeof(old);
	assert_d_eq(mallctl(name, (void *)&old, &sz, NULL, 0), 0,
	    "%s():%d: Unexpected mallctl failure reading %s", func, line, name);
	assert_b_eq(old, expected, "%s():%d: Unexpected %s value", func, line,
	    name);
}
