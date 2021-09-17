static bool
rtree_leaf_valid(rtree_leaf_elm_t *leaf) {
	return ((uintptr_t)leaf != (uintptr_t)0);
}
