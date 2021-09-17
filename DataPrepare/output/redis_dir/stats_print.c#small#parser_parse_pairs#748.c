static bool
parser_parse_pairs(parser_t *parser) {
	assert_d_eq(parser->token.token_type, TOKEN_TYPE_STRING,
	    "Object should start with string");
	if (parser_parse_pair(parser)) {
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
			switch (parser->token.token_type) {
			case TOKEN_TYPE_STRING:
				if (parser_parse_pair(parser)) {
					return true;
				}
				break;
			default:
				return true;
			}
			break;
		case TOKEN_TYPE_RBRACE:
			return false;
		default:
			return true;
		}
	}
}
