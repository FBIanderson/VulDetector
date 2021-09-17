static void
init_entries(ring_t *entries) {
	unsigned i;

	for (i = 0; i < NENTRIES; i++) {
		qr_new(&entries[i], link);
		entries[i].id = 'a' + i;
	}
}
