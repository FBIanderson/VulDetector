void
test_fail(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	malloc_vcprintf(NULL, NULL, format, ap);
	va_end(ap);
	malloc_printf("\n");
	test_status = test_status_fail;
}
