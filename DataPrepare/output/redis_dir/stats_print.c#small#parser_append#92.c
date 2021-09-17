static bool
parser_append(parser_t *parser, const char *str) {
	size_t len = strlen(str);
	char *buf = (parser->buf == NULL) ? mallocx(len + 1,
	    MALLOCX_TCACHE_NONE) : rallocx(parser->buf, parser->len + len + 1,
	    MALLOCX_TCACHE_NONE);
	if (buf == NULL) {
		return true;
	}
	memcpy(&buf[parser->len], str, len + 1);
	parser->buf = buf;
	parser->len += len;
	return false;
}
