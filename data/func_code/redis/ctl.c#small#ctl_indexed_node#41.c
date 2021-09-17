static const ctl_indexed_node_t *
ctl_indexed_node(const ctl_node_t *node) {
	return (!node->named ? (const ctl_indexed_node_t *)node : NULL);
}
