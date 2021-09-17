static bool
parser_parse(parser_t *parser) {
	if (parser_tokenize(parser)) {
		goto label_error;
	}
	if (parser_parse_value(parser)) {
		goto label_error;
	}

	if (parser_tokenize(parser)) {
		goto label_error;
	}
	switch (parser->token.token_type) {
	case TOKEN_TYPE_EOI:
		return false;
	default:
		goto label_error;
	}
	not_reached();

label_error:
	token_error(&parser->token);
	return true;
}
