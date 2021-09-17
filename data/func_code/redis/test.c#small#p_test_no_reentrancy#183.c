test_status_t
p_test_no_reentrancy(test_t *t, ...) {
	test_status_t ret;
	va_list ap;

	ret = test_status_pass;
	va_start(ap, t);
	ret = p_test_impl(true, false, t, ap);
	va_end(ap);

	return ret;
}
