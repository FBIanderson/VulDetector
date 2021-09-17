void
malloc_write(const char *s) {
	if (je_malloc_message != NULL) {
		je_malloc_message(NULL, s);
	} else {
		wrtmessage(NULL, s);
	}
}
