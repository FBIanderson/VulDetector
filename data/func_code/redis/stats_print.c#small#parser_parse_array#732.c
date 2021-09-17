static bool
parser_parse_array(parser_t *parser) {
	assert_d_eq(parser->token.token_type, TOKEN_TYPE_LBRACKET,
	    "Array should start with [");
	if (parser_tokenize(parser)) {
		return true;
	}
	switch (parser->token.token_type) {
	case TOKEN_TYPE_RBRACKET:
		return false;
	default:
		return parser_parse_values(parser);
	}
	not_reached();
}
