static int
node_cmp_magic(const node_t *a, const node_t *b) {

	assert_u32_eq(a->magic, NODE_MAGIC, "Bad magic");
	assert_u32_eq(b->magic, NODE_MAGIC, "Bad magic");

	return node_cmp(a, b);
}
