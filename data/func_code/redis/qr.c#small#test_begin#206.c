TEST_BEGIN(test_qr_meld_split) {
	ring_t entries[NENTRIES];
	unsigned i;

	init_entries(entries);
	for (i = 1; i < NENTRIES; i++) {
		qr_after_insert(&entries[i - 1], &entries[i], link);
	}

	qr_split(&entries[0], &entries[SPLIT_INDEX], ring_t, link);
	test_split_entries(entries);

	qr_meld(&entries[0], &entries[SPLIT_INDEX], ring_t, link);
	test_entries_ring(entries);

	qr_meld(&entries[0], &entries[SPLIT_INDEX], ring_t, link);
	test_split_entries(entries);

	qr_split(&entries[0], &entries[SPLIT_INDEX], ring_t, link);
	test_entries_ring(entries);

	qr_split(&entries[0], &entries[0], ring_t, link);
	test_entries_ring(entries);

	qr_meld(&entries[0], &entries[0], ring_t, link);
	test_entries_ring(entries);
}
