static rtree_node_elm_t *
rtree_child_node_read(tsdn_t *tsdn, rtree_t *rtree, rtree_node_elm_t *elm,
    unsigned level, bool dependent) {
	rtree_node_elm_t *node;

	node = rtree_child_node_tryread(elm, dependent);
	if (!dependent && unlikely(!rtree_node_valid(node))) {
		node = rtree_node_init(tsdn, rtree, level + 1, &elm->child);
	}
	assert(!dependent || node != NULL);
	return node;
}
