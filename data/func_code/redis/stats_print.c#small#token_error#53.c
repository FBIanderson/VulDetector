static void
token_error(token_t *token) {
	if (!token->parser->verbose) {
		return;
	}
	switch (token->token_type) {
	case TOKEN_TYPE_NONE:
		not_reached();
	case TOKEN_TYPE_ERROR:
		malloc_printf("%zu:%zu: Unexpected character in token: ",
		    token->line, token->col);
		break;
	default:
		malloc_printf("%zu:%zu: Unexpected token: ", token->line,
		    token->col);
		break;
	}
	UNUSED ssize_t err = malloc_write_fd(STDERR_FILENO,
	    &token->parser->buf[token->pos], token->len);
	malloc_printf("\n");
}
