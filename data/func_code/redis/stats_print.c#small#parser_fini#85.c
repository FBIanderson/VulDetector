static void
parser_fini(parser_t *parser) {
	if (parser->buf != NULL) {
		dallocx(parser->buf, MALLOCX_TCACHE_NONE);
	}
}
