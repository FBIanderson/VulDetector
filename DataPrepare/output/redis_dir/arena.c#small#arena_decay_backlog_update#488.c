static void
arena_decay_backlog_update(arena_decay_t *decay, uint64_t nadvance_u64,
    size_t current_npages) {
	if (nadvance_u64 >= SMOOTHSTEP_NSTEPS) {
		memset(decay->backlog, 0, (SMOOTHSTEP_NSTEPS-1) *
		    sizeof(size_t));
	} else {
		size_t nadvance_z = (size_t)nadvance_u64;

		assert((uint64_t)nadvance_z == nadvance_u64);

		memmove(decay->backlog, &decay->backlog[nadvance_z],
		    (SMOOTHSTEP_NSTEPS - nadvance_z) * sizeof(size_t));
		if (nadvance_z > 1) {
			memset(&decay->backlog[SMOOTHSTEP_NSTEPS -
			    nadvance_z], 0, (nadvance_z-1) * sizeof(size_t));
		}
	}

	arena_decay_backlog_update_last(decay, current_npages);
}
