static unsigned
do_arena_create(extent_hooks_t *h) {
	unsigned arena_ind;
	size_t sz = sizeof(unsigned);
	assert_d_eq(mallctl("arenas.create", (void *)&arena_ind, &sz,
	    (void *)(h != NULL ? &h : NULL), (h != NULL ? sizeof(h) : 0)), 0,
	    "Unexpected mallctl() failure");
	return arena_ind;
}
