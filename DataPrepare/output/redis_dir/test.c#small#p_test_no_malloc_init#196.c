test_status_t
p_test_no_malloc_init(test_t *t, ...) {
	test_status_t ret;
	va_list ap;

	ret = test_status_pass;
	va_start(ap, t);
	/*
	 * We also omit reentrancy from bootstrapping tests, since we don't
	 * (yet) care about general reentrancy during bootstrapping.
	 */
	ret = p_test_impl(false, false, t, ap);
	va_end(ap);

	return ret;
}
