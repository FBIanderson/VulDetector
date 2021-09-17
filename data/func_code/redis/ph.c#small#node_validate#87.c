static unsigned
node_validate(const node_t *node, const node_t *parent) {
	unsigned nnodes = 1;
	node_t *leftmost_child, *sibling;

	if (parent != NULL) {
		assert_d_ge(node_cmp_magic(node, parent), 0,
		    "Child is less than parent");
	}

	leftmost_child = phn_lchild_get(node_t, link, node);
	if (leftmost_child == NULL) {
		return nnodes;
	}
	assert_ptr_eq((void *)phn_prev_get(node_t, link, leftmost_child),
	    (void *)node, "Leftmost child does not link to node");
	nnodes += node_validate(leftmost_child, node);

	for (sibling = phn_next_get(node_t, link, leftmost_child); sibling !=
	    NULL; sibling = phn_next_get(node_t, link, sibling)) {
		assert_ptr_eq(phn_next_get(node_t, link, phn_prev_get(node_t,
		    link, sibling)), sibling,
		    "sibling's prev doesn't link to sibling");
		nnodes += node_validate(sibling, node);
	}
	return nnodes;
}
