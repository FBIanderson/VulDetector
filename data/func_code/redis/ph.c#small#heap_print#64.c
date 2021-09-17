static void
heap_print(const heap_t *heap) {
	node_t *auxelm;

	malloc_printf("vvv heap %p vvv\n", heap);
	if (heap->ph_root == NULL) {
		goto label_return;
	}

	node_print(heap->ph_root, 0);

	for (auxelm = phn_next_get(node_t, link, heap->ph_root); auxelm != NULL;
	    auxelm = phn_next_get(node_t, link, auxelm)) {
		assert_ptr_eq(phn_next_get(node_t, link, phn_prev_get(node_t,
		    link, auxelm)), auxelm,
		    "auxelm's prev doesn't link to auxelm");
		node_print(auxelm, 0);
	}

label_return:
	malloc_printf("^^^ heap %p ^^^\n", heap);
}
