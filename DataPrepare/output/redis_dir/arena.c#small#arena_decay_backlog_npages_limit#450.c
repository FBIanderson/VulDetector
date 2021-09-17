static size_t
arena_decay_backlog_npages_limit(const arena_decay_t *decay) {
	uint64_t sum;
	size_t npages_limit_backlog;
	unsigned i;

	/*
	 * For each element of decay_backlog, multiply by the corresponding
	 * fixed-point smoothstep decay factor.  Sum the products, then divide
	 * to round down to the nearest whole number of pages.
	 */
	sum = 0;
	for (i = 0; i < SMOOTHSTEP_NSTEPS; i++) {
		sum += decay->backlog[i] * h_steps[i];
	}
	npages_limit_backlog = (size_t)(sum >> SMOOTHSTEP_BFP);

	return npages_limit_backlog;
}
