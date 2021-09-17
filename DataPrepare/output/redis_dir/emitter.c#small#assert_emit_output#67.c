static void
assert_emit_output(void (*emit_fn)(emitter_t *),
    const char *expected_json_output, const char *expected_table_output) {
	emitter_t emitter;
	char buf[MALLOC_PRINTF_BUFSIZE];
	buf_descriptor_t buf_descriptor;

	buf_descriptor.buf = buf;
	buf_descriptor.len = MALLOC_PRINTF_BUFSIZE;
	buf_descriptor.mid_quote = false;

	emitter_init(&emitter, emitter_output_json, &forwarding_cb,
	    &buf_descriptor);
	(*emit_fn)(&emitter);
	assert_str_eq(expected_json_output, buf, "json output failure");

	buf_descriptor.buf = buf;
	buf_descriptor.len = MALLOC_PRINTF_BUFSIZE;
	buf_descriptor.mid_quote = false;

	emitter_init(&emitter, emitter_output_table, &forwarding_cb,
	    &buf_descriptor);
	(*emit_fn)(&emitter);
	assert_str_eq(expected_table_output, buf, "table output failure");
}
