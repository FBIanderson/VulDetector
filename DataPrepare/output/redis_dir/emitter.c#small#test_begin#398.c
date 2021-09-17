TEST_BEGIN(test_table_row) {
	assert_emit_output(&emit_table_row, table_row_json, table_row_table);
}
