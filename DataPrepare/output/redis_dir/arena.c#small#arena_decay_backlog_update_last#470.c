static void
arena_decay_backlog_update_last(arena_decay_t *decay, size_t current_npages) {
	size_t npages_delta = (current_npages > decay->nunpurged) ?
	    current_npages - decay->nunpurged : 0;
	decay->backlog[SMOOTHSTEP_NSTEPS-1] = npages_delta;

	if (config_debug) {
		if (current_npages > decay->ceil_npages) {
			decay->ceil_npages = current_npages;
		}
		size_t npages_limit = arena_decay_backlog_npages_limit(decay);
		assert(decay->ceil_npages >= npages_limit);
		if (decay->ceil_npages > npages_limit) {
			decay->ceil_npages = npages_limit;
		}
	}
}
