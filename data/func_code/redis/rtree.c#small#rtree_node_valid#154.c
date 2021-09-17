static bool
rtree_node_valid(rtree_node_elm_t *node) {
	return ((uintptr_t)node != (uintptr_t)0);
}
