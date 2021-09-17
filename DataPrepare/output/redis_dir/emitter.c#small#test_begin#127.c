TEST_BEGIN(test_dict) {
	assert_emit_output(&emit_dict, dict_json, dict_table);
}
