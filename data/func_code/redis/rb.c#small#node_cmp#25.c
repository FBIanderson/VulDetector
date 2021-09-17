static int
node_cmp(const node_t *a, const node_t *b) {
	int ret;

	assert_u32_eq(a->magic, NODE_MAGIC, "Bad magic");
	assert_u32_eq(b->magic, NODE_MAGIC, "Bad magic");

	ret = (a->key > b->key) - (a->key < b->key);
	if (ret == 0) {
		/*
		 * Duplicates are not allowed in the tree, so force an
		 * arbitrary ordering for non-identical items with equal keys.
		 */
		ret = (((uintptr_t)a) > ((uintptr_t)b))
		    - (((uintptr_t)a) < ((uintptr_t)b));
	}
	return ret;
}
