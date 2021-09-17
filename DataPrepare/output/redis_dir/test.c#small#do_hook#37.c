static void
do_hook(bool *hook_ran, void (**hook)()) {
	*hook_ran = true;
	*hook = NULL;

	size_t alloc_size = 1;
	for (int i = 0; i < NUM_REENTRANT_ALLOCS; i++) {
		free(malloc(alloc_size));
		alloc_size *= 2;
	}
}
