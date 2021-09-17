TEST_BEGIN(test_ql_tail_insert) {
	list_head_t head;
	list_t entries[NENTRIES];
	unsigned i;

	ql_new(&head);
	init_entries(entries, sizeof(entries)/sizeof(list_t));
	for (i = 0; i < NENTRIES; i++) {
		ql_tail_insert(&head, &entries[i], link);
	}

	test_entries_list(&head, entries, NENTRIES);
}
