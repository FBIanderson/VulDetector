static void
test_independent_entries(ring_t *entries) {
	ring_t *t;
	unsigned i, j;

	for (i = 0; i < NENTRIES; i++) {
		j = 0;
		qr_foreach(t, &entries[i], link) {
			j++;
		}
		assert_u_eq(j, 1,
		    "Iteration over single-element ring should visit precisely "
		    "one element");
	}
	for (i = 0; i < NENTRIES; i++) {
		j = 0;
		qr_reverse_foreach(t, &entries[i], link) {
			j++;
		}
		assert_u_eq(j, 1,
		    "Iteration over single-element ring should visit precisely "
		    "one element");
	}
	for (i = 0; i < NENTRIES; i++) {
		t = qr_next(&entries[i], link);
		assert_ptr_eq(t, &entries[i],
		    "Next element in single-element ring should be same as "
		    "current element");
	}
	for (i = 0; i < NENTRIES; i++) {
		t = qr_prev(&entries[i], link);
		assert_ptr_eq(t, &entries[i],
		    "Previous element in single-element ring should be same as "
		    "current element");
	}
}
