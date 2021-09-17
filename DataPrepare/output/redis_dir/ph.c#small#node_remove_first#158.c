static node_t *
node_remove_first(heap_t *heap) {
	node_t *node = heap_remove_first(heap);
	node->magic = 0;
	return node;
}
