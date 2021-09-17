static node_t *
remove_iterate_cb(tree_t *tree, node_t *node, void *data) {
	unsigned *nnodes = (unsigned *)data;
	node_t *ret = tree_next(tree, node);

	node_remove(tree, node, *nnodes);

	return ret;
}
