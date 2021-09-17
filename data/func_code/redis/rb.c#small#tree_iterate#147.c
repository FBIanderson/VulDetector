static unsigned
tree_iterate(tree_t *tree) {
	unsigned i;

	i = 0;
	tree_iter(tree, NULL, tree_iterate_cb, (void *)&i);

	return i;
}
