static malloc_mutex_t *
prof_gctx_mutex_choose(void) {
	unsigned ngctxs = atomic_fetch_add_u(&cum_gctxs, 1, ATOMIC_RELAXED);

	return &gctx_locks[(ngctxs - 1) % PROF_NCTX_LOCKS];
}
