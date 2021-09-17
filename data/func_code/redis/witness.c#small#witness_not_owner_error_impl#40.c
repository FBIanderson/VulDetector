static void
witness_not_owner_error_impl(const witness_t *witness) {
	malloc_printf("<jemalloc>: Should not own %s(%u)\n", witness->name,
	    witness->rank);
	abort();
}
