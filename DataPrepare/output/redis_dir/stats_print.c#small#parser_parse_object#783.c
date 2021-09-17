static bool
parser_parse_object(parser_t *parser) {
	assert_d_eq(parser->token.token_type, TOKEN_TYPE_LBRACE,
	    "Object should start with {");
	if (parser_tokenize(parser)) {
		return true;
	}
	switch (parser->token.token_type) {
	case TOKEN_TYPE_STRING:
		return parser_parse_pairs(parser);
	case TOKEN_TYPE_RBRACE:
		return false;
	default:
		return true;
	}
	not_reached();
}
