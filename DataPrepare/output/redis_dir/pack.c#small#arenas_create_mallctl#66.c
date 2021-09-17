static unsigned
arenas_create_mallctl(void) {
	unsigned arena_ind;
	size_t sz;

	sz = sizeof(arena_ind);
	assert_d_eq(mallctl("arenas.create", (void *)&arena_ind, &sz, NULL, 0),
	    0, "Error in arenas.create");

	return arena_ind;
}
