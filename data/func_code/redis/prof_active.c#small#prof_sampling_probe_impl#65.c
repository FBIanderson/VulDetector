static void
prof_sampling_probe_impl(bool expect_sample, const char *func, int line) {
	void *p;
	size_t expected_backtraces = expect_sample ? 1 : 0;

	assert_zu_eq(prof_bt_count(), 0, "%s():%d: Expected 0 backtraces", func,
	    line);
	p = mallocx(1, 0);
	assert_ptr_not_null(p, "Unexpected mallocx() failure");
	assert_zu_eq(prof_bt_count(), expected_backtraces,
	    "%s():%d: Unexpected backtrace count", func, line);
	dallocx(p, 0);
}
