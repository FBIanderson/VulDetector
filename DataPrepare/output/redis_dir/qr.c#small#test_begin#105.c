TEST_BEGIN(test_qr_after_insert) {
	ring_t entries[NENTRIES];
	unsigned i;

	init_entries(entries);
	for (i = 1; i < NENTRIES; i++) {
		qr_after_insert(&entries[i - 1], &entries[i], link);
	}
	test_entries_ring(entries);
}
