static rtree_leaf_elm_t *
rtree_child_leaf_read(tsdn_t *tsdn, rtree_t *rtree, rtree_node_elm_t *elm,
    unsigned level, bool dependent) {
	rtree_leaf_elm_t *leaf;

	leaf = rtree_child_leaf_tryread(elm, dependent);
	if (!dependent && unlikely(!rtree_leaf_valid(leaf))) {
		leaf = rtree_leaf_init(tsdn, rtree, &elm->child);
	}
	assert(!dependent || leaf != NULL);
	return leaf;
}
