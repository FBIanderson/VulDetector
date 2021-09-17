static void *
alloc_from_permuted_backtrace(unsigned thd_ind, unsigned iteration) {
	return btalloc(1, thd_ind*NALLOCS_PER_THREAD + iteration);
}
