static unsigned
arena_ind(void) {
	static unsigned ind = 0;

	if (ind == 0) {
		size_t sz = sizeof(ind);
		assert_d_eq(mallctl("arenas.create", (void *)&ind, &sz, NULL,
		    0), 0, "Unexpected mallctl failure creating arena");
	}

	return ind;
}
