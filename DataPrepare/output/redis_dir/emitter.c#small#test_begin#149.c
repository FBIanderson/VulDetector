TEST_BEGIN(test_table_printf) {
	assert_emit_output(&emit_table_printf, table_printf_json,
	    table_printf_table);
}
