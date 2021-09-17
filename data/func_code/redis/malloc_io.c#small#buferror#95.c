int
buferror(int err, char *buf, size_t buflen) {
#ifdef _WIN32
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, 0,
	    (LPSTR)buf, (DWORD)buflen, NULL);
	return 0;
#elif defined(JEMALLOC_STRERROR_R_RETURNS_CHAR_WITH_GNU_SOURCE) && defined(_GNU_SOURCE)
	char *b = strerror_r(err, buf, buflen);
	if (b != buf) {
		strncpy(buf, b, buflen);
		buf[buflen-1] = '\0';
	}
	return 0;
#else
	return strerror_r(err, buf, buflen);
#endif
}
