static void
wrtmessage(void *cbopaque, const char *s) {
	malloc_write_fd(STDERR_FILENO, s, strlen(s));
}
