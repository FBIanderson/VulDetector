static bool
parser_parse_value(parser_t *parser) {
	switch (parser->token.token_type) {
	case TOKEN_TYPE_NULL:
	case TOKEN_TYPE_FALSE:
	case TOKEN_TYPE_TRUE:
	case TOKEN_TYPE_STRING:
	case TOKEN_TYPE_NUMBER:
		return false;
	case TOKEN_TYPE_LBRACE:
		return parser_parse_object(parser);
	case TOKEN_TYPE_LBRACKET:
		return parser_parse_array(parser);
	default:
		return true;
	}
	not_reached();
}
