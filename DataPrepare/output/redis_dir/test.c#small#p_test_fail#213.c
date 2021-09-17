void
p_test_fail(const char *prefix, const char *message) {
	malloc_cprintf(NULL, NULL, "%s%s\n", prefix, message);
	test_status = test_status_fail;
}
