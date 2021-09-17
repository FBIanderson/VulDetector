static unsigned
heap_validate(const heap_t *heap) {
	unsigned nnodes = 0;
	node_t *auxelm;

	if (heap->ph_root == NULL) {
		goto label_return;
	}

	nnodes += node_validate(heap->ph_root, NULL);

	for (auxelm = phn_next_get(node_t, link, heap->ph_root); auxelm != NULL;
	    auxelm = phn_next_get(node_t, link, auxelm)) {
		assert_ptr_eq(phn_next_get(node_t, link, phn_prev_get(node_t,
		    link, auxelm)), auxelm,
		    "auxelm's prev doesn't link to auxelm");
		nnodes += node_validate(auxelm, NULL);
	}

label_return:
	if (false) {
		heap_print(heap);
	}
	return nnodes;
}
