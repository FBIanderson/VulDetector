TEST_BEGIN(test_json_parser) {
	size_t i;
	const char *invalid_inputs[] = {
		/* Tokenizer error case tests. */
		"{ \"string\": X }",
		"{ \"string\": nXll }",
		"{ \"string\": nuXl }",
		"{ \"string\": nulX }",
		"{ \"string\": nullX }",
		"{ \"string\": fXlse }",
		"{ \"string\": faXse }",
		"{ \"string\": falXe }",
		"{ \"string\": falsX }",
		"{ \"string\": falseX }",
		"{ \"string\": tXue }",
		"{ \"string\": trXe }",
		"{ \"string\": truX }",
		"{ \"string\": trueX }",
		"{ \"string\": \"\n\" }",
		"{ \"string\": \"\\z\" }",
		"{ \"string\": \"\\uX000\" }",
		"{ \"string\": \"\\u0X00\" }",
		"{ \"string\": \"\\u00X0\" }",
		"{ \"string\": \"\\u000X\" }",
		"{ \"string\": -X }",
		"{ \"string\": 0.X }",
		"{ \"string\": 0.0eX }",
		"{ \"string\": 0.0e+X }",

		/* Parser error test cases. */
		"{\"string\": }",
		"{\"string\" }",
		"{\"string\": [ 0 }",
		"{\"string\": {\"a\":0, 1 } }",
		"{\"string\": {\"a\":0: } }",
		"{",
		"{}{",
	};
	const char *valid_inputs[] = {
		/* Token tests. */
		"null",
		"false",
		"true",
		"{}",
		"{\"a\": 0}",
		"[]",
		"[0, 1]",
		"0",
		"1",
		"10",
		"-10",
		"10.23",
		"10.23e4",
		"10.23e-4",
		"10.23e+4",
		"10.23E4",
		"10.23E-4",
		"10.23E+4",
		"-10.23",
		"-10.23e4",
		"-10.23e-4",
		"-10.23e+4",
		"-10.23E4",
		"-10.23E-4",
		"-10.23E+4",
		"\"value\"",
		"\" \\\" \\/ \\b \\n \\r \\t \\u0abc \\u1DEF \"",

		/* Parser test with various nesting. */
		"{\"a\":null, \"b\":[1,[{\"c\":2},3]], \"d\":{\"e\":true}}",
	};

	for (i = 0; i < sizeof(invalid_inputs)/sizeof(const char *); i++) {
		const char *input = invalid_inputs[i];
		parser_t parser;
		parser_init(&parser, false);
		assert_false(parser_append(&parser, input),
		    "Unexpected input appending failure");
		assert_true(parser_parse(&parser),
		    "Unexpected parse success for input: %s", input);
		parser_fini(&parser);
	}

	for (i = 0; i < sizeof(valid_inputs)/sizeof(const char *); i++) {
		const char *input = valid_inputs[i];
		parser_t parser;
		parser_init(&parser, true);
		assert_false(parser_append(&parser, input),
		    "Unexpected input appending failure");
		assert_false(parser_parse(&parser),
		    "Unexpected parse error for input: %s", input);
		parser_fini(&parser);
	}
}
