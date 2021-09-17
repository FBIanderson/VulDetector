TEST_BEGIN(test_ph_empty) {
	heap_t heap;

	heap_new(&heap);
	assert_true(heap_empty(&heap), "Heap should be empty");
	assert_ptr_null(heap_first(&heap), "Unexpected node");
	assert_ptr_null(heap_any(&heap), "Unexpected node");
}
