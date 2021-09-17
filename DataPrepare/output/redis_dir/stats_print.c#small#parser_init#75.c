static void
parser_init(parser_t *parser, bool verbose) {
	parser->verbose = verbose;
	parser->buf = NULL;
	parser->len = 0;
	parser->pos = 0;
	parser->line = 1;
	parser->col = 0;
}
