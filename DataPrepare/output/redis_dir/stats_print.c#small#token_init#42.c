static void
token_init(token_t *token, parser_t *parser, token_type_t token_type,
    size_t pos, size_t len, size_t line, size_t col) {
	token->parser = parser;
	token->token_type = token_type;
	token->pos = pos;
	token->len = len;
	token->line = line;
	token->col = col;
}
