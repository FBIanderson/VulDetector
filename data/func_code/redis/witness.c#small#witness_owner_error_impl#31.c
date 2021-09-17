static void
witness_owner_error_impl(const witness_t *witness) {
	malloc_printf("<jemalloc>: Should own %s(%u)\n", witness->name,
	    witness->rank);
	abort();
}
