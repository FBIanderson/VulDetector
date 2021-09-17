TEST_BEGIN(test_qr_one) {
	ring_t entries[NENTRIES];

	init_entries(entries);
	test_independent_entries(entries);
}
