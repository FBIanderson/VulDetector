TEST_BEGIN(test_json_arr) {
	assert_emit_output(&emit_json_arr, json_arr_json, json_arr_table);
}
