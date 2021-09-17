static bool
prof_dump_printf(bool propagate_err, const char *format, ...) {
	bool ret;
	va_list ap;
	char buf[PROF_PRINTF_BUFSIZE];

	va_start(ap, format);
	malloc_vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);
	ret = prof_dump_write(propagate_err, buf);

	return ret;
}
