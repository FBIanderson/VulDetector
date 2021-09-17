static void
mallctl_bool_set(const char *name, bool old_expected, bool val_new,
    const char *func, int line) {
	bool old;
	size_t sz;

	sz = sizeof(old);
	assert_d_eq(mallctl(name, (void *)&old, &sz, (void *)&val_new,
	    sizeof(val_new)), 0,
	    "%s():%d: Unexpected mallctl failure reading/writing %s", func,
	    line, name);
	assert_b_eq(old, old_expected, "%s():%d: Unexpected %s value", func,
	    line, name);
}
