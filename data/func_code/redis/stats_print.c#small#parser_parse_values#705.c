static bool
parser_parse_values(parser_t *parser) {
	if (parser_parse_value(parser)) {
		return true;
	}

	while (true) {
		if (parser_tokenize(parser)) {
			return true;
		}
		switch (parser->token.token_type) {
		case TOKEN_TYPE_COMMA:
			if (parser_tokenize(parser)) {
				return true;
			}
			if (parser_parse_value(parser)) {
				return true;
			}
			break;
		case TOKEN_TYPE_RBRACKET:
			return false;
		default:
			return true;
		}
	}
}
