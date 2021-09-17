TEST_BEGIN(test_ql_empty) {
	list_head_t head;

	ql_new(&head);
	test_empty_list(&head);
}
