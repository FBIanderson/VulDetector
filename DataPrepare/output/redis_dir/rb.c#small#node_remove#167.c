static void
node_remove(tree_t *tree, node_t *node, unsigned nnodes) {
	node_t *search_node;
	unsigned black_height, imbalances;

	tree_remove(tree, node);

	/* Test rb_nsearch(). */
	search_node = tree_nsearch(tree, node);
	if (search_node != NULL) {
		assert_u64_ge(search_node->key, node->key,
		    "Key ordering error");
	}

	/* Test rb_psearch(). */
	search_node = tree_psearch(tree, node);
	if (search_node != NULL) {
		assert_u64_le(search_node->key, node->key,
		    "Key ordering error");
	}

	node->magic = 0;

	rbtn_black_height(node_t, link, tree, black_height);
	imbalances = tree_recurse(tree->rbt_root, black_height, 0);
	assert_u_eq(imbalances, 0, "Tree is unbalanced");
	assert_u_eq(tree_iterate(tree), nnodes-1,
	    "Unexpected node iteration count");
	assert_u_eq(tree_iterate_reverse(tree), nnodes-1,
	    "Unexpected node iteration count");
}
