static void
witness_depth_error_impl(const witness_list_t *witnesses,
    witness_rank_t rank_inclusive, unsigned depth) {
	witness_t *w;

	malloc_printf("<jemalloc>: Should own %u lock%s of rank >= %u:", depth,
	    (depth != 1) ?  "s" : "", rank_inclusive);
	ql_foreach(w, witnesses, link) {
		malloc_printf(" %s(%u)", w->name, w->rank);
	}
	malloc_printf("\n");
	abort();
}
