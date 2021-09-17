static const ctl_named_node_t *
ctl_named_node(const ctl_node_t *node) {
	return ((node->named) ? (const ctl_named_node_t *)node : NULL);
}
