TEST_BEGIN(test_nested_dict) {
	assert_emit_output(&emit_nested_dict, nested_dict_json,
	    nested_dict_table);
}
