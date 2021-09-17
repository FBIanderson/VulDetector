static rtree_node_elm_t *
rtree_child_node_tryread(rtree_node_elm_t *elm, bool dependent) {
	rtree_node_elm_t *node;

	if (dependent) {
		node = (rtree_node_elm_t *)atomic_load_p(&elm->child,
		    ATOMIC_RELAXED);
	} else {
		node = (rtree_node_elm_t *)atomic_load_p(&elm->child,
		    ATOMIC_ACQUIRE);
	}

	assert(!dependent || node != NULL);
	return node;
}
