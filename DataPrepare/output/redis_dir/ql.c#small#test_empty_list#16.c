static void
test_empty_list(list_head_t *head) {
	list_t *t;
	unsigned i;

	assert_ptr_null(ql_first(head), "Unexpected element for empty list");
	assert_ptr_null(ql_last(head, link),
	    "Unexpected element for empty list");

	i = 0;
	ql_foreach(t, head, link) {
		i++;
	}
	assert_u_eq(i, 0, "Unexpected element for empty list");

	i = 0;
	ql_reverse_foreach(t, head, link) {
		i++;
	}
	assert_u_eq(i, 0, "Unexpected element for empty list");
}
