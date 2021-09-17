static const ctl_named_node_t *
ctl_named_children(const ctl_named_node_t *node, size_t index) {
	const ctl_named_node_t *children = ctl_named_node(node->children);

	return (children ? &children[index] : NULL);
}
