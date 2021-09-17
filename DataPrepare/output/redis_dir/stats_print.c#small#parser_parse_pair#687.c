static bool
parser_parse_pair(parser_t *parser) {
	assert_d_eq(parser->token.token_type, TOKEN_TYPE_STRING,
	    "Pair should start with string");
	if (parser_tokenize(parser)) {
		return true;
	}
	switch (parser->token.token_type) {
	case TOKEN_TYPE_COLON:
		if (parser_tokenize(parser)) {
			return true;
		}
		return parser_parse_value(parser);
	default:
		return true;
	}
}
