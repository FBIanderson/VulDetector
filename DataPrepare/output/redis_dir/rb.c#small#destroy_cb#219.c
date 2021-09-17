static void
destroy_cb(node_t *node, void *data) {
	unsigned *nnodes = (unsigned *)data;

	assert_u_gt(*nnodes, 0, "Destruction removed too many nodes");
	(*nnodes)--;
}
