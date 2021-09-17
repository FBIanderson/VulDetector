bool
malloc_initialized(void) {
	return (malloc_init_state == malloc_init_initialized);
}
