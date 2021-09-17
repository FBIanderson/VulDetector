static void
test_entries_list(list_head_t *head, list_t *entries, unsigned nentries) {
	list_t *t;
	unsigned i;

	assert_c_eq(ql_first(head)->id, entries[0].id, "Element id mismatch");
	assert_c_eq(ql_last(head, link)->id, entries[nentries-1].id,
	    "Element id mismatch");

	i = 0;
	ql_foreach(t, head, link) {
		assert_c_eq(t->id, entries[i].id, "Element id mismatch");
		i++;
	}

	i = 0;
	ql_reverse_foreach(t, head, link) {
		assert_c_eq(t->id, entries[nentries-i-1].id,
		    "Element id mismatch");
		i++;
	}

	for (i = 0; i < nentries-1; i++) {
		t = ql_next(head, &entries[i], link);
		assert_c_eq(t->id, entries[i+1].id, "Element id mismatch");
	}
	assert_ptr_null(ql_next(head, &entries[nentries-1], link),
	    "Unexpected element");

	assert_ptr_null(ql_prev(head, &entries[0], link), "Unexpected element");
	for (i = 1; i < nentries; i++) {
		t = ql_prev(head, &entries[i], link);
		assert_c_eq(t->id, entries[i-1].id, "Element id mismatch");
	}
}
