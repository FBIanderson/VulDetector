static rtree_leaf_elm_t *
rtree_child_leaf_tryread(rtree_node_elm_t *elm, bool dependent) {
	rtree_leaf_elm_t *leaf;

	if (dependent) {
		leaf = (rtree_leaf_elm_t *)atomic_load_p(&elm->child,
		    ATOMIC_RELAXED);
	} else {
		leaf = (rtree_leaf_elm_t *)atomic_load_p(&elm->child,
		    ATOMIC_ACQUIRE);
	}

	assert(!dependent || leaf != NULL);
	return leaf;
}
