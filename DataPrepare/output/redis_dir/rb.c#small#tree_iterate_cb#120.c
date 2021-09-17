static node_t *
tree_iterate_cb(tree_t *tree, node_t *node, void *data) {
	unsigned *i = (unsigned *)data;
	node_t *search_node;

	assert_u32_eq(node->magic, NODE_MAGIC, "Bad magic");

	/* Test rb_search(). */
	search_node = tree_search(tree, node);
	assert_ptr_eq(search_node, node,
	    "tree_search() returned unexpected node");

	/* Test rb_nsearch(). */
	search_node = tree_nsearch(tree, node);
	assert_ptr_eq(search_node, node,
	    "tree_nsearch() returned unexpected node");

	/* Test rb_psearch(). */
	search_node = tree_psearch(tree, node);
	assert_ptr_eq(search_node, node,
	    "tree_psearch() returned unexpected node");

	(*i)++;

	return NULL;
}
