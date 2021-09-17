static void
node_print(const node_t *node, unsigned depth) {
	unsigned i;
	node_t *leftmost_child, *sibling;

	for (i = 0; i < depth; i++) {
		malloc_printf("\t");
	}
	malloc_printf("%2"FMTu64"\n", node->key);

	leftmost_child = phn_lchild_get(node_t, link, node);
	if (leftmost_child == NULL) {
		return;
	}
	node_print(leftmost_child, depth + 1);

	for (sibling = phn_next_get(node_t, link, leftmost_child); sibling !=
	    NULL; sibling = phn_next_get(node_t, link, sibling)) {
		node_print(sibling, depth + 1);
	}
}
