static void
emit_dict(emitter_t *emitter) {
	bool b_false = false;
	bool b_true = true;
	int i_123 = 123;
	const char *str = "a string";

	emitter_begin(emitter);
	emitter_dict_begin(emitter, "foo", "This is the foo table:");
	emitter_kv(emitter, "abc", "ABC", emitter_type_bool, &b_false);
	emitter_kv(emitter, "def", "DEF", emitter_type_bool, &b_true);
	emitter_kv_note(emitter, "ghi", "GHI", emitter_type_int, &i_123,
	    "note_key1", emitter_type_string, &str);
	emitter_kv_note(emitter, "jkl", "JKL", emitter_type_string, &str,
	    "note_key2", emitter_type_bool, &b_false);
	emitter_dict_end(emitter);
	emitter_end(emitter);
}
