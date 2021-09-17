static unsigned
tree_iterate_reverse(tree_t *tree) {
	unsigned i;

	i = 0;
	tree_reverse_iter(tree, NULL, tree_iterate_cb, (void *)&i);

	return i;
}
