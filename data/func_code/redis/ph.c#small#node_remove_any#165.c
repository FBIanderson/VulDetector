static node_t *
node_remove_any(heap_t *heap) {
	node_t *node = heap_remove_any(heap);
	node->magic = 0;
	return node;
}
