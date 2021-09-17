static int
witness_comp(const witness_t *a, void *oa, const witness_t *b, void *ob) {
	assert_u_eq(a->rank, b->rank, "Witnesses should have equal rank");

	assert(oa == (void *)a);
	assert(ob == (void *)b);

	return strcmp(a->name, b->name);
}
