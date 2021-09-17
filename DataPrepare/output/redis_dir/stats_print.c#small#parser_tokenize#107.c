static bool
parser_tokenize(parser_t *parser) {
	enum {
		STATE_START,
		STATE_EOI,
		STATE_N, STATE_NU, STATE_NUL, STATE_NULL,
		STATE_F, STATE_FA, STATE_FAL, STATE_FALS, STATE_FALSE,
		STATE_T, STATE_TR, STATE_TRU, STATE_TRUE,
		STATE_LBRACKET,
		STATE_RBRACKET,
		STATE_LBRACE,
		STATE_RBRACE,
		STATE_COLON,
		STATE_COMMA,
		STATE_CHARS,
		STATE_CHAR_ESCAPE,
		STATE_CHAR_U, STATE_CHAR_UD, STATE_CHAR_UDD, STATE_CHAR_UDDD,
		STATE_STRING,
		STATE_MINUS,
		STATE_LEADING_ZERO,
		STATE_DIGITS,
		STATE_DECIMAL,
		STATE_FRAC_DIGITS,
		STATE_EXP,
		STATE_EXP_SIGN,
		STATE_EXP_DIGITS,
		STATE_ACCEPT
	} state = STATE_START;
	size_t token_pos JEMALLOC_CC_SILENCE_INIT(0);
	size_t token_line JEMALLOC_CC_SILENCE_INIT(1);
	size_t token_col JEMALLOC_CC_SILENCE_INIT(0);

	assert_zu_le(parser->pos, parser->len,
	    "Position is past end of buffer");

	while (state != STATE_ACCEPT) {
		char c = parser->buf[parser->pos];

		switch (state) {
		case STATE_START:
			token_pos = parser->pos;
			token_line = parser->line;
			token_col = parser->col;
			switch (c) {
			case ' ': case '\b': case '\n': case '\r': case '\t':
				break;
			case '\0':
				state = STATE_EOI;
				break;
			case 'n':
				state = STATE_N;
				break;
			case 'f':
				state = STATE_F;
				break;
			case 't':
				state = STATE_T;
				break;
			case '[':
				state = STATE_LBRACKET;
				break;
			case ']':
				state = STATE_RBRACKET;
				break;
			case '{':
				state = STATE_LBRACE;
				break;
			case '}':
				state = STATE_RBRACE;
				break;
			case ':':
				state = STATE_COLON;
				break;
			case ',':
				state = STATE_COMMA;
				break;
			case '"':
				state = STATE_CHARS;
				break;
			case '-':
				state = STATE_MINUS;
				break;
			case '0':
				state = STATE_LEADING_ZERO;
				break;
			case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				state = STATE_DIGITS;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_EOI:
			token_init(&parser->token, parser,
			    TOKEN_TYPE_EOI, token_pos, parser->pos -
			    token_pos, token_line, token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_N:
			switch (c) {
			case 'u':
				state = STATE_NU;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_NU:
			switch (c) {
			case 'l':
				state = STATE_NUL;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_NUL:
			switch (c) {
			case 'l':
				state = STATE_NULL;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_NULL:
			switch (c) {
			case ' ': case '\b': case '\n': case '\r': case '\t':
			case '\0':
			case '[': case ']': case '{': case '}': case ':':
			case ',':
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			token_init(&parser->token, parser, TOKEN_TYPE_NULL,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_F:
			switch (c) {
			case 'a':
				state = STATE_FA;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_FA:
			switch (c) {
			case 'l':
				state = STATE_FAL;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_FAL:
			switch (c) {
			case 's':
				state = STATE_FALS;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_FALS:
			switch (c) {
			case 'e':
				state = STATE_FALSE;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_FALSE:
			switch (c) {
			case ' ': case '\b': case '\n': case '\r': case '\t':
			case '\0':
			case '[': case ']': case '{': case '}': case ':':
			case ',':
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			token_init(&parser->token, parser,
			    TOKEN_TYPE_FALSE, token_pos, parser->pos -
			    token_pos, token_line, token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_T:
			switch (c) {
			case 'r':
				state = STATE_TR;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_TR:
			switch (c) {
			case 'u':
				state = STATE_TRU;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_TRU:
			switch (c) {
			case 'e':
				state = STATE_TRUE;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_TRUE:
			switch (c) {
			case ' ': case '\b': case '\n': case '\r': case '\t':
			case '\0':
			case '[': case ']': case '{': case '}': case ':':
			case ',':
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			token_init(&parser->token, parser, TOKEN_TYPE_TRUE,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_LBRACKET:
			token_init(&parser->token, parser, TOKEN_TYPE_LBRACKET,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_RBRACKET:
			token_init(&parser->token, parser, TOKEN_TYPE_RBRACKET,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_LBRACE:
			token_init(&parser->token, parser, TOKEN_TYPE_LBRACE,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_RBRACE:
			token_init(&parser->token, parser, TOKEN_TYPE_RBRACE,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_COLON:
			token_init(&parser->token, parser, TOKEN_TYPE_COLON,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_COMMA:
			token_init(&parser->token, parser, TOKEN_TYPE_COMMA,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_CHARS:
			switch (c) {
			case '\\':
				state = STATE_CHAR_ESCAPE;
				break;
			case '"':
				state = STATE_STRING;
				break;
			case 0x00: case 0x01: case 0x02: case 0x03: case 0x04:
			case 0x05: case 0x06: case 0x07: case 0x08: case 0x09:
			case 0x0a: case 0x0b: case 0x0c: case 0x0d: case 0x0e:
			case 0x0f: case 0x10: case 0x11: case 0x12: case 0x13:
			case 0x14: case 0x15: case 0x16: case 0x17: case 0x18:
			case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d:
			case 0x1e: case 0x1f:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			default:
				break;
			}
			break;
		case STATE_CHAR_ESCAPE:
			switch (c) {
			case '"': case '\\': case '/': case 'b': case 'n':
			case 'r': case 't':
				state = STATE_CHARS;
				break;
			case 'u':
				state = STATE_CHAR_U;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_CHAR_U:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f':
			case 'A': case 'B': case 'C': case 'D': case 'E':
			case 'F':
				state = STATE_CHAR_UD;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_CHAR_UD:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f':
			case 'A': case 'B': case 'C': case 'D': case 'E':
			case 'F':
				state = STATE_CHAR_UDD;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_CHAR_UDD:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f':
			case 'A': case 'B': case 'C': case 'D': case 'E':
			case 'F':
				state = STATE_CHAR_UDDD;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_CHAR_UDDD:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f':
			case 'A': case 'B': case 'C': case 'D': case 'E':
			case 'F':
				state = STATE_CHARS;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_STRING:
			token_init(&parser->token, parser, TOKEN_TYPE_STRING,
			    token_pos, parser->pos - token_pos, token_line,
			    token_col);
			state = STATE_ACCEPT;
			break;
		case STATE_MINUS:
			switch (c) {
			case '0':
				state = STATE_LEADING_ZERO;
				break;
			case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				state = STATE_DIGITS;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_LEADING_ZERO:
			switch (c) {
			case '.':
				state = STATE_DECIMAL;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_NUMBER, token_pos, parser->pos -
				    token_pos, token_line, token_col);
				state = STATE_ACCEPT;
				break;
			}
			break;
		case STATE_DIGITS:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				break;
			case '.':
				state = STATE_DECIMAL;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_NUMBER, token_pos, parser->pos -
				    token_pos, token_line, token_col);
				state = STATE_ACCEPT;
				break;
			}
			break;
		case STATE_DECIMAL:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				state = STATE_FRAC_DIGITS;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_FRAC_DIGITS:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				break;
			case 'e': case 'E':
				state = STATE_EXP;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_NUMBER, token_pos, parser->pos -
				    token_pos, token_line, token_col);
				state = STATE_ACCEPT;
				break;
			}
			break;
		case STATE_EXP:
			switch (c) {
			case '-': case '+':
				state = STATE_EXP_SIGN;
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				state = STATE_EXP_DIGITS;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_EXP_SIGN:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				state = STATE_EXP_DIGITS;
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_ERROR, token_pos, parser->pos + 1
				    - token_pos, token_line, token_col);
				return true;
			}
			break;
		case STATE_EXP_DIGITS:
			switch (c) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				break;
			default:
				token_init(&parser->token, parser,
				    TOKEN_TYPE_NUMBER, token_pos, parser->pos -
				    token_pos, token_line, token_col);
				state = STATE_ACCEPT;
				break;
			}
			break;
		default:
			not_reached();
		}

		if (state != STATE_ACCEPT) {
			if (c == '\n') {
				parser->line++;
				parser->col = 0;
			} else {
				parser->col++;
			}
			parser->pos++;
		}
	}
	return false;
}
